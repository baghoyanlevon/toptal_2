MAINTAINER Levon Baghoyan
ENV PYTHONUNBUFFERED 1

COPY ./requirements.txt /requirements.txt

RUN apk add --update --no-cache postgresql-client
RUN apk add --update --no-cache --virtual .tmp-build-deps \
      gcc libc-dev linux-headers postgresql-dev musl-dev zlib zlib-dev libressl-dev
RUN pip install -r /requirements.txt
RUN python -m pip install uwsgi
RUN mkdir /MPIBlurryFaces
WORKDIR /MPIBlurryFaces
COPY ./app /MPIBlurryFaces

RUN adduser -D user
USER user
