# TEST TASK YADRO.

## Проект собирается на Windows и Linux c с помощью cmake

Снала необходимо клонировать репозиторий с помощью :
```
git clone https://github.com/awssed/YadroTestTask
```
## Windows:

Чтобы собрать и скомпилировать проект на Windows, необходимо иметь установленный cmake и mingw с соответсвующими установленными записями в PATH.

Если все условия выше выполнены, то необходимо запустить build.bat
```
build.bat
```

После этого появится папка build c исполняемым файлом.

Пример запуска:
```
TestTaskYadro.exe input.txt
```

## Linux:
Чтобы собрать и скомпилировать проект на Cmake, необходимо иметь установленный gcc, clang и CMAKE.

Скачав всё необходимое, нужно запустить файл buildLinux.sh:
```
chmod +x buildLinux.sh
./buildLinux.sh
```

После этого появиться исполняемый файл TestTaskYadro
## Важно!
## Если при запуске в Linux появляется ошибка неправильно формата, то необходимо поставить во входном текстовом файле параметр LineEnding на Unix/Linux через текстовый редактор.
Пример запуска:
```
./TestTaskYadro input.txt
```

