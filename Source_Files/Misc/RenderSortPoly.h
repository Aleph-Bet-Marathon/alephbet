#ifndef _RENDER_SORT_POLYGONS_CLASS_
#define _RENDER_SORT_POLYGONS_CLASS_
/*
	
	Rendering Polygon-Sorting Class
	by Loren Petrich,
	August 6, 2000
	
	Defines a class for sorting the polygons into appropriate depth order; from render.c
	Works from RenderVisTree stuff.
	
	Made [view_data *view] a member and removed it as an argument
*/

#include "GrowableList.h"
#include "ResizableList.h"
#include "world.h"
#include "render.h"
#include "RenderVisTree.h"


/* ---------- sorted nodes */

struct sorted_node_data
{
	short polygon_index;
	
	struct render_object_data *interior_objects;
	struct render_object_data *exterior_objects;
	
	struct clipping_window_data *clipping_windows;
};


class RenderSortPolyClass
{
	// Auxiliary data and routines:

	void initialize_sorted_render_tree();
	
	clipping_window_data *build_clipping_windows(node_data *ChainBegin);

	void calculate_vertical_clip_data(line_clip_data **accumulated_line_clips,
		short accumulated_line_clip_count, clipping_window_data *window, short x0, short x1);
		
public:
	
	 /* converts map polygon indexes to sorted nodes (only valid if _polygon_is_visible) */
	ResizableList<sorted_node_data *> polygon_index_to_sorted_node;
	
	// LP additions: growable list of sorted nodes
	// Length changed in initialize_sorted_render_tree() and sort_render_tree()
	// When being built, the render objects are yet to be listed
	GrowableList<sorted_node_data> SortedNodes;
	
	// LP addition: growable lists of accumulations of endpoint and line clips
	// used in build_clipping_windows()
	GrowableList<endpoint_clip_data *> AccumulatedEndpointClips;
	GrowableList<line_clip_data *> AccumulatedLineClips;

	// Pointers to view and calculated visibility tree
	view_data *view;
	RenderVisTreeClass *RVPtr;
	
	// Resizes all the objects defined inside;
	// the resizing is lazy
	void Resize(int NumPolygons);

	// Does the sorting
	void sort_render_tree();
  	
  	// Inits everything
 	RenderSortPolyClass();
};

// Historical note: cause of too-many-transparent-line errors
// LP addition: node-alias growable list
// Only used in sort_render_tree()
// Suppressed as unnecessary because of node_data polygon-sorted-tree structure
// static GrowableList<node_data *> NodeAliases(32);


#endif
