# drewgonzales360 

This is just a place to keep my notes and an explanation of this. I hope that this directory can help anyone who finds it. 

I used https://jhelvy.shinyapps.io/qmkjsonconverter/ to go from the qmk layout json to c.

## Building

```
qmk compile -kb keebio/iris/rev6 -km drewgonzales360
qmk flash -kb keebio/iris/rev6 -km drewgonzales360
```

## Notes
Oh. You do have access to the OS.
https://github.com/rafaelromao/keyboards/blob/main/src/qmk/users/rafaelromao/features/window_swapper.c#L10
