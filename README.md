# Технологии и методы программирования

## Сервер

### Запуск в контейнере

> Linux/Unix

```
docker buildx build ./server -t tcpserver_image
docker run --rm -p 33333:33333 --name tcpserver tcpserver_image
```

### Ручная сборка

> Linux/Unix

```
mkdir ./server/build
cd ./server/build
cmake ..
make
```
