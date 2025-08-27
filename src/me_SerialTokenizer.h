// Get entity from Serial

/*
  Entity is a sequence of non-space characters.
*/

/*
  Author: Martin Eden
  Last mod.: 2025-08-27
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_SerialTokenizer
{
  class TSerialTokenizer
  {
    public:
      // Time to wait for character on empty stream
      TUint_2 BreakTimeout_ms = 15;

      // Get entity from UART
      TBool GetEntity(
        TAddressSegment * Capture,
        TAddressSegment Buffer
      );

      // Wait until we get something
      void WaitEntity(
        TAddressSegment * Capture,
        TAddressSegment Buffer
      );

    protected:
      TBool HasPeekCharacter = false;
      TUint_1 PeekCharacter;

      TBool RetrievePeekCharacter() __attribute__((optimize("O0")));
      void PurgePeekCharacter();
      void PurgeSpaces();
      TBool PurgeEntity();
  };

  // Freetown
  namespace Freetown
  {
    TBool IsSpace(TUint_1 Char);
  }
}

/*
  2024-05-08
  2024-05-13
  2024-05-19 entity capture is a custom record
  2024-05-23 entity is a memseg. capture result is outer record
  2024-10-27
    [~] Switching to [me_Uart] from [HardwareSerial]
    [/] It is class now because I need to store timeout somewhere
    [-] Dropped TCapturedEntity. Usage overhead and no need
*/
