echo "Checking GitHub Pages configuration..."

API_URL="https://api.github.com/repos/$GITHUB_REPOSITORY/pages"

HTTP_STATUS=$(curl \
  --silent \
  --write-out "%{http_code}" \
  --output response.json \
  -H "Authorization: Bearer $GITHUB_TOKEN" \
  -H "Accept: application/vnd.github+json" \
  "https://api.github.com/repos/$GITHUB_REPOSITORY/pages")

echo "HTTP status: $HTTP_STATUS"

if [[ "$HTTP_STATUS" -ne 200 ]]; then
  echo "Pages API not accessible."
  echo "enabled=false" >> "$GITHUB_OUTPUT"
  exit 0
fi

BUILD_TYPE=$(jq -r '.build_type' response.json)

echo "build_type=$BUILD_TYPE"

if [[ "$BUILD_TYPE" == "workflow" ]]; then
  echo "GitHub Pages is deployed via GitHub Actions."
  echo "enabled=true" >> "$GITHUB_OUTPUT"
else
  echo "GitHub Pages is deployed from branch."
  echo "enabled=false" >> "$GITHUB_OUTPUT"
fi
