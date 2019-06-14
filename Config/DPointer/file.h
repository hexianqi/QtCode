/***************************************************************************************************
**      %{CurrentDate:yyyy-MM-dd}  %{CN}
***************************************************************************************************/

#ifndef %{GUARD}
#define %{GUARD}

@if '%{Base}'
#include "%{Base}.h"
@endif

%{BN}

class %{CNP};

@if '%{Base}'
class %{CN} : public %{Base}
@else
class %{CN}
@endif
{
@if %{isQObject}
    Q_OBJECT
@endif
@if %{isInheritDPointer}
    Q_DECLARE_PRIVATE(%{CN})
@endif

public:
@if '%{InheritObject}'
    explicit %{CN}(%{InheritObject} *parent = nullptr);
@else
    explicit %{CN}();
@endif
@if '%{Base}'
    ~%{CN}() override;
@else
    virtual ~%{CN}();
@endif

protected:
@if '%{InheritObject}'
    %{CN}(%{CNP} &p, %{InheritObject} *parent = nullptr);
@else
    %{CN}(%{CNP} &);
@endif
@if %{isInheritDPointer}
@else

protected:
    QScopedPointer<%{CN}Private> d_ptr;
@endif
};

%{EN}

#endif // %{GUARD}\
