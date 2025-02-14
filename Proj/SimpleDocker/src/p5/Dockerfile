FROM nginx
WORKDIR /home/
COPY nginx.conf /etc/nginx/
COPY serv.c .
COPY script.sh .
RUN apt update &&  apt upgrade && apt install -y gcc spawn-fcgi libfcgi-dev && rm -rf /var/lib/apt/lists
RUN chown -R nginx:nginx /home
RUN chown -R nginx:nginx /etc/nginx/nginx.conf
RUN chown -R nginx:nginx /var/cache/nginx
RUN touch /var/run/nginx.pid
RUN chown -R nginx:nginx /var/run/nginx.pid
USER nginx


HEALTHCHECK NONE
ENTRYPOINT ["sh","./script.sh"]