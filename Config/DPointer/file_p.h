#ifndef %{GUARDP}
#define %{GUARDP}

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

#endif // %{GUARDP}\
