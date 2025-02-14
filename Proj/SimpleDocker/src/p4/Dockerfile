FROM nginx:latest
WORKDIR /home/
COPY nginx.conf /etc/nginx/nginx.conf
COPY serv.c /home/serv.c
COPY script.sh /home/script.sh
RUN apt update &&  apt upgrade && apt install -y gcc spawn-fcgi libfcgi-dev
rm -rf /var/lib/apt/lists/*
HEALTHCHECK NONE;
ENTRYPOINT ["sh","./script.sh"]