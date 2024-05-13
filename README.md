
# github 연습용 리포지트

> https://velog.io/@lazysia/git-github-desktop-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0

***

## 마크 다운 작성법
> [한국어 설명 사이트](https://www.heropy.dev/p/B74sNE)
### 헤더 작성법
<pre>
  # Header 1
  ## Header 2
  ### Header 3 ...
</pre>
최대 6번까지 사용 가능

> # Header 1
> ## Header 2
> ### Header 3 

### 글자 강조
<pre>
  *single asterisks*
  _single underscores_
  **double asterisks**
  __double underscores__
  ~~cancel line~~
</pre>
- *single asterisks*
- _single underscores_
- **doublle asterisks**
- __single underscores__
- ~~cancel line~~

### 글머리 기호: *,+,- 지원
<pre>
  * full circle
    * circle
      * full rect
        * full rect
</pre>
혼합해서 사용하는 것도 가능하다.
* circle
    * circle
        * rect
            * rect

### 코드 사용
<pre>
  ```python
  class People():
    def __init__():
      print("Hello")
  ```
</pre>
```python
def Hello():
  print("Hello")
```

### 링크 문법 구조
<pre>
  [이름](링크)
  [이름](링크 "설명")
  [이름][참조]

  [참조]: 링크
  [참조]: 링크 "설명"
</pre>

[네이버](https://naver.com "naver site")
