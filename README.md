# img420-assignment-2

In this project, I created a FadingSprite node, which extends Sprite2d and comes with custom fade in and fade out animations, configurable with rotation over time, scaling over time, both of which are configurable in the editor, and the ability to reverse the animation and fade directions using 2 booleans passed to the start_animation function.

1. Two new features extended from Sprite2D: Scaling and rotation
2. Parameters available in the editor: Scale (X and Y), Rotation, and Animation Duration
3. One signal emitted by this node that triggers an action in an existing node: Await animation complete in _on_body_entered in win_area.gd script
4. One method in this node that is triggered by emitting a signal in one of the existing nodes: start_animation(true, true) call in the _on_player_game_started function in the win_area.gd script

5. Interesting animations: My scaling, fading, and rotation animation engine does not use the build in animation library. I do not have time to implement pause and stop, but the play button could be considered to be the start_animation method call (maybe 1 point of extra credit?). 
