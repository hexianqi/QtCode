#include "%{PriFileName}"

%{BN}

@if %{isInheritDPointer}
%{CN}::%{CN}(%{JS: ('%{InheritObject}') ? '%{InheritObject} *parent' : ''}) :
    %{Base}(*new %{CNP}%{JS: ('%{InheritObject}') ? ', parent' : ''})
{
}

%{CN}::%{CN}(%{CNP} &p%{JS: ('%{InheritObject}') ? ', %{InheritObject} *parent' : ''}) :
    %{Base}(p%{JS: ('%{InheritObject}') ? ', parent' : ''})
{
}
@else
%{CN}::%{CN}(%{JS: ('%{InheritObject}') ? '%{InheritObject} *parent' : ''}) :
    @if '%{Base}'
    %{Base}(%{JS: ('%{InheritObject}') ? 'parent' : ''}),
    @endif
    d_ptr(new %{CNP})
{
}

%{CN}::%{CN}(%{CNP} &p%{JS: ('%{InheritObject}') ? ', %{InheritObject} *parent' : ''}) :
    @if '%{Base}'
    %{Base}(%{JS: ('%{InheritObject}') ? 'parent' : ''}),
    @endif
    d_ptr(&p)
{
}
@endif

%{CN}::~%{CN}()
{
}

%{EN}
