# CustomAssertionInCpp

커스텀 assert 매크로입니다.
윈도우 전용으로 작성했으며, <assert.h>의 assert 매크로와 유사하게 동작하도록 신경썼습니다.

```c++
#include "Assertion.hpp"

void useAssert()
{
    // assert
    MY_ASSERT(0 == 1);
}
```
