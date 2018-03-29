/**

 Copyright (c) 2018 National Instruments Corp.

 This software is subject to the terms described in the LICENSE.TXT file

 SDG
 */

/*! \file
 \brief Control refnum management

 Control references are defined in the Locals: block of a VI (or inside an EventSpec),
 and define a named, statically-bound reference to a control on a specific VI.
 
 Example:
 
 define(MyVI dv(.VirtualInstrument (
 Locals: c(
 e(ControlReference("dataItem_Foo") ctlref1)  // static control ref linked to dataItem_Foo
 ) ...
 
 The actual Type of ctlref1 is ControlRefNum and stores a refnum (cookie) which
 opaquely holds onto the VI and control tag (data item).
 The VI isn't passed directly, it's implicitly taken from the context,
 whatever VI the ControlReference is defined in.
 ControlRefNums defined with ControlReference() exist during the entire
 lifetime of the VI and are only deallocated when the last clump of the last
 top-level VI finishes.
 
 Non-statically-bound ControlRefNums variables can also be declared in the Params:
 or Locals: sections, e.g.  e(ControlRefNum ref).
 These can be used in subVIs to refer to a reference passed in by a caller.
*/

#ifndef ControlRef_h
#define ControlRef_h

#include "TypeAndDataManager.h"
#include "RefNum.h"

namespace Vireo
{

// Control RefNum API: create, lookup, and destroy control refnums
RefNum ControlReferenceCreate(VirtualInstrument *vi, const SubString &controlTag);
RefNum ControlReferenceCreate(RefNumVal *pRefNumVal, VirtualInstrument *vi, const SubString &controlTag);

NIError ControlReferenceLookup(RefNum refnum, VirtualInstrument **pVI, SubString *pControlTag);

NIError ControlReferenceDestroy(RefNum refnum);
NIError ControlReferenceAppendDescription(StringRef str, RefNum refnum);

}  // namespace Vireo

#endif  // ControlRef_h
