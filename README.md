# CustomAssertionInCpp

커스텀 assert 매크로입니다.
윈도우 전용으로 작성했으며, 단순 출력과 팝업 출력 두 가지 assert가 있습니다.

```c++
void useAssert()
{
  // assert
  ASSERT(0 == 1); // = check(0 == 1)
  ASSERT_M(false, "Test message"); // = checkm(false, "Test message");
  
  // popup assert
  int* pInt = nullptr;
  ASSERT_POPUP(nullptr != pInt);
  
  // debug break, print
  bool bPass = false;
  if( false == bPass )
  {
    int a = 321;
    DEBUG_PRINT_ERROR("bPass is false, %d", a);
  }
}
```
