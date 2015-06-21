GPU Rebooter
============
Disables and re-enables a display adapter on a captured keystroke to try to resolve issues.

This entire thing is a Bad Idea(tm) and will likely force you to restart applications that cannot recover from an unexpected loss of the display adapter.

The value in this application is if you have a particular need for reinitializing the display device, particularly if WDDM's TDR has failed in some spectacular way, or if some sort of memory error on the GPU has allowed artifacts to develop.

This isn't coded for general use, and in fact the display driver's name is hardcoded and there is no error handling. Use this at your own risk.

Godspeed.
