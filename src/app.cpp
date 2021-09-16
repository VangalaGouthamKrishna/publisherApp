#include <mosaiq/cyclicapp.h>
#include <stdio.h>

int counter = 0;

void DLL_EXPORT mosaiq_app_on_initialization()
{
  puts("stringpublisher was started");
}

void DLL_EXPORT mosaiq_app_on_cyclic_execution()
{
  ++counter;
}

void DLL_EXPORT mosaiq_app_on_exit()
{
  puts("stringpublisher was stopped");
}