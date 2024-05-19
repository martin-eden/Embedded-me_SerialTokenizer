// Get entity from Serial

/*
  Entity is a sequence of non-space characters.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-05-19
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_SerialTokenizer
{
  using namespace me_BaseTypes;
  using namespace me_MemorySegment;

  /*
    Entity record

      Chars: (char*)

        Pointer to ASCIIZ data.

      Length: ui2

        Length in ASCII characters.

      IsTrimmed: bool

        true, when entity would be longer if we had more memory for it
  */
  struct TEntity
  {
    TChar * Chars;
    TUint_2 Length;
    TBool IsTrimmed;
  };

  // Get entity from Serial
  TBool GetEntity(
    TEntity * EnityPtr,
    TMemorySegment CaptureBuffer
  );

  // Implementation

  TBool StreamIsEmpty();
  TBool StockPeek(TChar * Char);
  TBool PeekCharacter(TChar * Char);

  void PurgeCharacter();
  void PurgeSpaces();
  TBool PurgeEntity();
}

/*
  2024-05-08
  2024-05-13
  2024-05-19 entity capture is a memory segment
*/
