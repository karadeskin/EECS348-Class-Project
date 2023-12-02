#!/bin/bash

if [[ "14" != $(curl -s -d '{"expression": "2*7"}' -X POST http://localhost:3000/) ]]; then
    echo "test failed: 14 !=" $?
else
    echo "test passed"
fi
