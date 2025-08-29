// Getting entity from Serial

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

/*
  "Entity" is a sequence surrounded by "spaces".

  "Space" is space character, newline or "end of stream" condition.
*/

#include <me_SerialTokenizer.h>

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_StreamTools.h>
#include <me_StreamsCollection.h>

#include <Arduino.h> // for millis()

using namespace me_SerialTokenizer;

/*
  Get entity from serial stream.

  Entities that are larger than capture buffer are skipped.

  Example

    For capture buffer with 3 characters and stream "ABCD EFG",
    capture will be "EFG".

  Input

    TMemorySegment Buffer

      Memory segment where we will store bytes.

      It IS NOT data to parse. We are obtaining data to parse from
      Serial.

  Output

    TMemorySegment * Capture

      Subsegment in <Buffer> buffer where we have entity.

  Behavior

    We do not wait for non-space characters.

      If the stream was empty or only spaces were received then

        Capture.Size == 0
*/
TBool TSerialTokenizer::GetEntity(
  TAddressSegment * Capture,
  TAddressSegment Buffer
)
{
  me_StreamsCollection::TWorkmemOutputStream Buff_Stream;
  TAddressSegment Result;

  if (!Buff_Stream.Init(Buffer))
    return false;

  // <Result> points to the same memory as <Buffer>
  Result.Addr = Buffer.Addr;

  Redo:

  Result.Size = 0;

  PurgeSpaces();

  // Return on empty stream
  if (!HasPeekCharacter)
    return false;

  // Pre-condition: stream is at non-space
  while (true)
  {
    Buff_Stream.Write(PeekCharacter);

    PurgePeekCharacter();

    // Increase length
    ++Result.Size;

    // No place to store more?
    if (Result.Size == Buffer.Size)
    {
      TBool ThereWasMoreData = PurgeEntity();

      // Fish is too large, drop it
      if (ThereWasMoreData)
        goto Redo;

      break;
    }

    // Break if stream is empty
    if (!RetrievePeekCharacter())
      break;

    // Break if there is space under stream cursor
    if (Freetown::IsSpace(PeekCharacter))
      break;
  }
  // Post-condition: stream is empty or at space

  *Capture = Result;

  return true;
}

/*
  Wait entity from serial stream

  We will not return until we get something non-empty.
*/
void TSerialTokenizer::WaitEntity(
  TAddressSegment * Capture,
  TAddressSegment Buffer
)
{
  while (!GetEntity(Capture, Buffer));
}

/*
  Peek() is not possible via hardware UART.

  Reading data byte register initiates writing there next data byte.
  At hardware level.

  So we're using local buffer of one character. It will be returned
  by PeekCharacter() and will be the first victim of PurgeCharacter().
*/

/*
  Return next character in stream but do not extract it.
*/
TBool TSerialTokenizer::RetrievePeekCharacter()
{
  if (HasPeekCharacter)
    return true;

  TUint_1 Byte;
  TUint_4 WaitStopTime = millis() + BreakTimeout_ms;

  while (true)
  {
    if (me_Uart::GetByte(&Byte))
    {
      PeekCharacter = Byte;
      HasPeekCharacter = true;

      return true;
    }

    if (millis() >= WaitStopTime)
      return false;
  }
}

/*
  Drop peek character.

  This function is called when character is processed and we
  are ready for a new one.
*/
void TSerialTokenizer::PurgePeekCharacter()
{
  HasPeekCharacter = false;
}

/*
  Drop characters from stream
  until
    non-space character or
    end of stream
*/
void TSerialTokenizer::PurgeSpaces()
{
  while (true)
  {
    // Return on empty stream
    if (!RetrievePeekCharacter())
      return;

    // Return on non-space under cursor
    if (!Freetown::IsSpace(PeekCharacter))
      return;

    PurgePeekCharacter();
  }
}

/*
  Drop characters from stream
  until
    space character or
    end of stream

  Returns true when at least one non-space character was dropped.
*/
TBool TSerialTokenizer::PurgeEntity()
{
  TBool PurgedSomething = false;

  while (true)
  {
    if (!RetrievePeekCharacter())
      return PurgedSomething;

    if (Freetown::IsSpace(PeekCharacter))
      return PurgedSomething;

    PurgePeekCharacter();

    PurgedSomething = true;
  }

  return PurgedSomething;
}

// Freetown

/*
  Return true if character is newline or space

  Fuck that C standard library! Their isspace('\n') returns 252.
  Not zero, no questions.
*/
TBool Freetown::IsSpace(
  TUint_1 Char
)
{
  if (
    (Char == ' ') ||
    (Char == '\n') ||
    (Char == '\r') ||
    (Char == '\t') ||
    (Char == '\v')
  )
    return true;

  return false;
}


/*
  2024 # # # # # #
  2025-08-26
*/
