#!/bin/bash

find ~ -mtime 1 > modified:`date +%Y-%j-%T`
