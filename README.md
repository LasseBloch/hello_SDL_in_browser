# hello_SDL_in_browser
A first iteration of transcipting a small SDL application to run in a webbrowser, via emscripten

## To transpile to JS
Install emscripten

Example of build command:
```
emcc main.cpp -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["bmp"]' \
    --preload-file assets -o index.html
```

Example of starting a webserver to serve the generated html and JS files:
```
python3.7 -m http.server 8080
```