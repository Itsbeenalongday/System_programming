# System_programming

## Contents
+ 실습
  - 라즈베리 파일 실습
+ 과제
  - SIC/XE Architecture Assembly language
  - make algorithm written by assembly
  
## Sictool manual
```shell
# install

# remove <= 1.8 java
$ sudo apt-get remove openjdk* oracle*

# install 1.8 <= version java
$ sudo apt-get update
$ sudo apt-get install openjdk-8-jdk
$ git clone  https://github.com/jurem/SicTools.git
$ cd SitTools/
$ make jar

# file name is option 
$ java -jar out/make/sictools.jar <file_name>
```
+ make jar error
  - sictools 을 설치할 때 make jar 명령어로 빌드를 수행하면 javafx 관련 에러가 나오는 경우가 있습니다.   
    최근 배포되는 자바 sdk 에 jafafx (GUI 라이브러리) 가 기본 탑재되어서 나오지 않는 것으로 변경되어 발생하는 오류로 보여집니다.   
    아래 명령어로 missing dependency 를 해결해주세요   
  - [해결법 링크](https://askubuntu.com/questions/1137891/how-to-install-run-java-8-and-javafx-on-ubuntu-18-04)

+ error 해결 명령어 set
```shell
$ sudo apt install \
  openjfx=8u161-b12-1ubuntu2 \
  libopenjfx-java=8u161-b12-1ubuntu2 \
  libopenjfx-jni=8u161-b12-1ubuntu2
  
$ sudo apt-mark hold \
  openjfx \
  libopenjfx-java \
  libopenjfx-jni
```
