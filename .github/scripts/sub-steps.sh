#!/bin/bash

command="$@"

start_time=$(date +%s)
echo "::group::${command}"
eval "${command}"
echo "::endgroup::"
end_time=$(date +%s)
duration=$((end_time - start_time))
echo "duration(${command}) = ${duration}s"
