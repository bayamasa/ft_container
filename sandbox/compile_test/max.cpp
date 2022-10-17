// 暗黙的実態化をcppファイルで行っているためcompileエラーになる
// cppのcompileは分割compileなため、cppファイル単位でのcompileになる
// そのとき、実装の実態を持つmax.cppはmain.cppからだと見えないのでリンク時に未定義でcompileエラーになる
#include "max.h"
template<typename tType>
tType max(tType a, tType b)
{
    return (a >= b)?a:b;
}
