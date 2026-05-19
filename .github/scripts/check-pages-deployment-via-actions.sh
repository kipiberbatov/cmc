echo "Checking GitHub Pages mode..."

HTTP_STATUS=$(curl \
  --silent \
  --write-out "%{http_code}" \
  --output response.json \
  -H "Authorization: Bearer $GITHUB_TOKEN" \
  -H "Accept: application/vnd.github+json" \
  "https://api.github.com/repos/$GITHUB_REPOSITORY/pages")

if [[ "$HTTP_STATUS" != "200" ]]; then
  echo "GitHub Pages is not enabled (status=$HTTP_STATUS)"
  echo "pages_via_actions=false" >> "$GITHUB_OUTPUT"
  exit 0
fi

BUILD_TYPE=$(jq -r '.build_type' response.json)

if [[ "$BUILD_TYPE" == "workflow" ]]; then
  echo "GitHub Pages uses GitHub Actions"
  echo "pages_via_actions=true" >> "$GITHUB_OUTPUT"
else
  echo "GitHub Pages uses branch deployment (build_type=$BUILD_TYPE)"
  echo "pages_via_actions=false" >> "$GITHUB_OUTPUT"
fi
