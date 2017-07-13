/** 
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                     Version 2, December 2004
 *
 *  Copyright (C) 2017 Fabian Thuering
 *
 *  Everyone is permitted to copy and distribute verbatim or modified
 *  copies of this license document, and changing it is allowed as long
 *  as the name is changed.
 *
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 **/

#ifndef DYCORE_OPT 
#error "DYCORE_OPT not defined"
#endif

// #define DYCORE_OPT(Type, Name, DefaultValue, NeedsUpdate)
//
//  Type          -  C++ type of the option (has to be one of the supported types)
//  Name          -  Name of the option
//  DefaultValue  -  Default value of the option
//  NeedsUpate    -  Indicate whether the option needs to be recomputed once updated
//

DYCORE_OPT(int, itype_hdiff, 2, false) 
DYCORE_OPT(Real, dt, 30.0, true)
