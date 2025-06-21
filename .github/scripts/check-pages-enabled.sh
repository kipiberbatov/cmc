#!/bin/bash

echo "Checking for existence of environment: 'github-pages'"

HTTP_STATUS=$(curl --write-out "%{http_code}" --silent --output /dev/null \
  --header "Accept: application/vnd.github.v3+json" \
  "https://api.github.com/repos/$GITHUB_REPOSITORY/environments/github-pages")

if [[ "$HTTP_STATUS" -eq 200 ]]; then
  echo "Environment 'github-pages' found."
  echo "enabled=true" >> "$GITHUB_OUTPUT"
else
  echo "Environment 'github-pages' does not exist (HTTP status: $HTTP_STATUS)."
  echo "enabled=false" >> "$GITHUB_OUTPUT"
fi
