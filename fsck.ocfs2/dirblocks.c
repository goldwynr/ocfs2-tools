/* -*- mode: c; c-basic-offset: 8; -*-
 * vim: noexpandtab sw=8 ts=8 sts=0:
 *
 * icount.c
 *
 * As always, we let e2fsck lead the way.  A bitmap for
 * inodes with a single i_count (the vast majority), and a
 * tree of inode numbers with a greater count. 
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, version 2,  as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 *
 * Authors: Zach Brown
 */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>

#include "ocfs2.h"

#include "fsck.h"
#include "dirblocks.h"
#include "util.h"

void o2fsck_add_dir_block(o2fsck_dirblocks *db, uint64_t ino, uint64_t blkno, 
			uint64_t blkcount)
{
	struct rb_node ** p = &db->db_root.rb_node;
	struct rb_node * parent = NULL;
	o2fsck_dirblock_entry *dbe, *tmp_dbe;;

	dbe = calloc(1, sizeof(*dbe));
	if (dbe == NULL)
		fatal_error(OCFS2_ET_NO_MEMORY, 
				"while allocating directory entries");

	dbe->e_ino = ino;
	dbe->e_blkno = blkno;
	dbe->e_blkcount = blkcount;

	printf("inserting %"PRIu64" %"PRIu64" %"PRIu64"\n", dbe->e_ino, 
			dbe->e_blkno, dbe->e_blkcount);

	while (*p)
	{
		parent = *p;
		tmp_dbe = rb_entry(parent, o2fsck_dirblock_entry, e_node);

		if (dbe->e_blkno < tmp_dbe->e_blkno)
			p = &(*p)->rb_left;
		else if (dbe->e_blkno > tmp_dbe->e_blkno)
			p = &(*p)->rb_right;
	}

	rb_link_node(&dbe->e_node, parent, p);
	rb_insert_color(&dbe->e_node, &db->db_root);
}

void o2fsck_dir_block_iterate(o2fsck_dirblocks *db, dirblock_iterator func,
				void *priv_data)
{
	o2fsck_dirblock_entry *dbe;
	struct rb_node *node;
	unsigned ret;

	for(node = rb_first(&db->db_root); node; node = rb_next(node)) {
		dbe = rb_entry(node, o2fsck_dirblock_entry, e_node);
		ret = func(dbe, priv_data);
		if (ret & OCFS2_DIRENT_ABORT)
			return;
	}
}