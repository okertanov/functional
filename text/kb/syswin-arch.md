
Window System
=============

* Session (DM, User Context, Auth, etc.)
  * Viewport (Visible area, HW viewpoint)
    * Window Manager (UX)
      * Layouts
        - Placement
        - Arrangement
        - Grid
        - Stack
        - Tiling
      * Root Window (Parent, recursive)
        - Windows
        - Panels
        - Launchers
        - Gadgets
      * Client windows
        - Style/Shape
        - Non-client area
          - Title
          - Icon
          - Window controls
        - Client area
          - Context
          - Painting
          - UI Toolkits & Controls (recursive Client window)
      * Interactions
        - User input
        - Show/Hide
        - Selection
        - Movement
        - Sizing
        - Overlap/Intersections
        - DnD
        - Animtion/Effects
        - Compositing
  * Messaging
    - UI Loop/Queue
    - Events
    - Inter-client/Inter-process communications
    - Clipboard
  * Renderer
    - Vectors
    - Surfaces
    - Shapes
    - Overlays
    - Rasterizers
  * Resources
    - Assets (strings, images, fonts)
    - Id's (pid, guid, handles)
    - UI DSL resources

