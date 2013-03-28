# `env`
A C library for manipulating env pairs

## Introduction
The way environment variables are represented in C is an array of strings,
formed as `NAME=value`. This will be further referred to as a env pair.
`env` is a library to make manipulating such arrays really easy and as close
to node's `process.env` as possible.

## API
API is documented in [`include/env.h`](https://github.com/mmalecki/env/blob/master/include/env.h).

## Usage
Executing `make` in the project tree results in a `libenv.a` to be created. You
can link this library statically to your project.
