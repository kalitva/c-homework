- Устанавливаем `autoreconf`, если не установлен. Также, возможно, понадобится установить
`automake` и `libtool`
```shell
sudo apt install autoconf automake libtool
```

- Скачиваем репозиторий и заходим в него
```shell
git clone https://github.com/curl/curl.git && cd curl
```

- Генерируем `configure` скрипт
```shell
autoreconf -fi
```

- Настраиваем сборку, включив в нее только `http`, `https` и `telnet` протоколы
```shell
 ./configure --without-libpsl \
    --disable-dict \
    --disable-file \
    --disable-ftp \
    --disable-gopher \
    --disable-imap \
    --disable-ipfs \
    --disable-mqtt \
    --disable-pop3 \
    --disable-rtsp \
    --disable-smtp \
    --disable-tftp \
    --disable-websockets \
    --with-ssl \
    --disable-smb
```

- Собираем
```shell
make
```

- Проверяем
```shell
$ src/curl --version
curl 8.12.0-DEV (x86_64-pc-linux-gnu) libcurl/8.12.0-DEV OpenSSL/3.0.15 zlib/1.2.13
Release-Date: [unreleased]
Protocols: http https telnet
Features: alt-svc AsynchDNS HSTS HTTPS-proxy IPv6 Largefile libz NTLM SSL threadsafe TLS-SRP UnixSockets
```
