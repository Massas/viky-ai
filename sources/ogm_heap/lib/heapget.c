/*
 *  Adding cells
 *  Copyright (c) 2010 Pertimm by Patrick Constant
 *  Dev : November 2010
 *  Version 1.0
 */
#include "ogm_heap.h"

// print backtrace
#include <execinfo.h>

/**
 * Getting a buffer : pointer to the <b>last used position</b> of the heap, makes sure the heap
 * is big enough to accomodate nb_added_cells cells.
 * Note : The heap IS NOT reset.
 *
 * \param handle handle to a memory heap API
 * \param nb_added_cells number of cells garantied to be allocated
 * \return the pointer to the buffer of nb_added_cells cells, NULL or error
 **/
PUBLIC(void *) OgHeapGetBufferNew(og_heap ctrl_heap, size_t nb_added_cells)
{
  if (ctrl_heap->type != DOgHeapTypeNormal)
  {
    og_char_buffer erreur[DOgErrorSize];
    snprintf(erreur, DOgErrorSize, "OgHeapGetFullSizedBuffer on '%s', heap must be normal type (%d)",
        ctrl_heap->name, ctrl_heap->type);
    OgErr(ctrl_heap->herr, erreur);
    OG_LOG_BACKTRACE(ctrl_heap->hmsg, erreur);

    return NULL;
  }

  // get previews cells used
  size_t previews_cells_used = OgHeapGetCellsUsed(ctrl_heap);
  IF(previews_cells_used) return NULL;

  // ensure buffer is big enough
  IF(OgHeapTestReallocInternal(ctrl_heap, nb_added_cells)) return NULL;

  // Mark all added cells as used by the buffer
  IF(OgHeapSetCellsUsed(ctrl_heap, previews_cells_used + nb_added_cells)) return NULL;

  // return buffer pointer from the lasted use cell
  return HeapNormalGetCell(ctrl_heap, previews_cells_used);

}

/**
 * Getting a buffer : pointer to the <b>beginning</b> of the heap, makes sure the heap
 * is big enough to accomodate nb_added_cells cells.
 * Note : The heap IS RESET.
 *
 * \param handle handle to a memory heap API
 * \param buffer_cell_number new cell number in the heap
 * \return the pointer to the buffer of nb_added_cells cells, NULL or error
 **/
PUBLIC(void *) OgHeapGetBufferReuse(og_heap ctrl_heap, size_t nb_added_cells)
{

  if (ctrl_heap->type != DOgHeapTypeNormal)
  {
    og_char_buffer erreur[DOgErrorSize];
    snprintf(erreur, DOgErrorSize, "OgHeapGetFullSizedBuffer on '%s', heap must be normal type (%d)",
        ctrl_heap->name, ctrl_heap->type);
    OgErr(ctrl_heap->herr, erreur);
    OG_LOG_BACKTRACE(ctrl_heap->hmsg, erreur);

    return NULL;
  }

  // reset buffer used
  IF(OgHeapResetWithoutReduce(ctrl_heap)) return NULL;

  // ensure buffer is big enough
  IF(OgHeapTestReallocInternal(ctrl_heap, nb_added_cells)) return NULL;

  // Mark all added cells as used by the buffer
  IF(OgHeapSetCellsUsed(ctrl_heap, nb_added_cells)) return NULL;

  // return buffer pointer from the beginning
  return HeapNormalGetCell(ctrl_heap, 0);

}

/**
 * Getting a pointer to the cell whose index is cell_index
 * OgHeapGetCell(handle,cell_index)
 *
 * \param handle handle to a memory heap API
 * \param cell_index cell index
 * \return the pointer to the cell, and 0 on error
 **/
PUBLIC(void *) OgHeapGetCell(og_heap handle, size_t cell_index)
{
  struct og_ctrl_heap *ctrl_heap = (struct og_ctrl_heap *)handle;

  og_char_buffer erreur[DOgErrorSize];

  if (cell_index == (size_t) -1)
  {
    snprintf(erreur, DOgErrorSize, "OgHeapGetCell on '%s': cell_index == -1", ctrl_heap->name);
    OgErr(ctrl_heap->herr, erreur);
    OG_LOG_BACKTRACE(ctrl_heap->hmsg, erreur);

    return NULL;
  }

  if (cell_index >= OgHeapGetCellsNumber(ctrl_heap))
  {
    snprintf(erreur, DOgErrorSize, "OgHeapGetCell on '%s': cell_index (%ld) >= OgHeapGetCellsNumber (%ld)",
        ctrl_heap->name, cell_index, OgHeapGetCellsNumber(ctrl_heap));
    OgErr(ctrl_heap->herr, erreur);
    OG_LOG_BACKTRACE(ctrl_heap->hmsg, erreur);

    return NULL;
  }

  // TODO OgHeapGetCell change to >= , it may crash a lot of test
  else if (cell_index != 0 && cell_index > ctrl_heap->cells_used)
  {
    snprintf(erreur, DOgErrorSize, "OgHeapGetCell on '%s': cell_index (%ld) >= ctrl_heap->cells_used (%ld)",
        ctrl_heap->name, cell_index, ctrl_heap->cells_used);
    OgErr(ctrl_heap->herr, erreur);
    OG_LOG_BACKTRACE(ctrl_heap->hmsg, erreur);

    return NULL;
  }

  if (ctrl_heap->type == DOgHeapTypeSliced)
  {
    return HeapSliceGetCell(ctrl_heap, cell_index);
  }
  else if (ctrl_heap->type == DOgHeapTypeNormal)
  {
    return HeapNormalGetCell(ctrl_heap, cell_index);
  }
  else
  {
    snprintf(erreur, DOgErrorSize, "OgHeapGetCell on '%s': function not yet implemented for heap type (%d)",
        ctrl_heap->name, ctrl_heap->type);
    OgErr(ctrl_heap->herr, erreur);
    OG_LOG_BACKTRACE(ctrl_heap->hmsg, erreur);

    return NULL;
  }

}

inline void *HeapSliceGetCell(struct og_ctrl_heap *ctrl_heap, size_t cell_index)
{
  size_t Islice = cell_index / ctrl_heap->nb_cells_per_slice;
  size_t cell_index_in_slice = cell_index % ctrl_heap->nb_cells_per_slice;
  size_t cell_start = cell_index_in_slice * ctrl_heap->cell_size;

  struct slice *slice = HeapNormalGetCell(ctrl_heap->hslice, Islice);
  IFn(slice) return NULL;

  return ((void *) (slice->heap + cell_start));
}

inline void *HeapNormalGetCell(struct og_ctrl_heap *ctrl_heap, size_t cell_index)
{
  size_t cell_start = cell_index * ctrl_heap->cell_size;
  return ((void *) (ctrl_heap->normal_heap + cell_start));
}

