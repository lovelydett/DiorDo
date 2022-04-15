// Logging
// Created by Yuting Xie
// 2022/4/15

// Todo(yuting): use GLOG

#ifndef DIORDO_LOGGING_H
#define DIORDO_LOGGING_H

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING

#include <cstdio>

#define LOG_INFO(format, ...)                                                  \
  fprintf(stdout, "[Info][%s:%d]\t", __FILE__, __LINE__);                      \
  /* Add ## here to compile in Linux if empty args */                          \
  fprintf(stdout, format, ##__VA_ARGS__);                                      \
  fprintf(stdout, "\n");

#define LOG_ERR(format, ...)                                                   \
  fprintf(stderr, "[Error][%s:%d]\t", __FILE__, __LINE__);                     \
  fprintf(stderr, format, ##__VA_ARGS__);                                      \
  fprintf(stderr, "\n");

#else

#define LOG_INFO(format, ...) ;
#define LOG_ERR(format, ...) ;

#endif

#endif // DIORDO_LOGGING_H
