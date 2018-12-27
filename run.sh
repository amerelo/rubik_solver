#!/usr/bin/env bash
cd algo &&
cargo build --release &&
cd .. &&
cmake . &&
make &&
cd ./bin &&
./rubik &&
cd ..