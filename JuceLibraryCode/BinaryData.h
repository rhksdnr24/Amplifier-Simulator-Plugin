/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Gibson_J45_2_48000_wav;
    const int            Gibson_J45_2_48000_wavSize = 6188;

    extern const char*   Gibson_J45_2_48000_Match_wav;
    const int            Gibson_J45_2_48000_Match_wavSize = 6188;

    extern const char*   Acoustasonic_Mex3_48k_Ph_Qck_Std_wav;
    const int            Acoustasonic_Mex3_48k_Ph_Qck_Std_wavSize = 3116;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 3;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
