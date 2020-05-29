@if '%{Cpp:PragmaOnce}'
#pragma once
@else
#ifndef %{GUARDP}
#define %{GUARDP}
@endif

#include "%{HdrFileName}"
@if %{isInheritDPointer}
#include "%{Base}_p.h"
@endif

%{BN}

@if %{isInheritDPointer}
class %{CNP} : public %{Base}Private
@else
class %{CNP}
@endif
{

};

%{EN}

@if ! '%{Cpp:PragmaOnce}'
#endif // %{GUARDP}
@endif
