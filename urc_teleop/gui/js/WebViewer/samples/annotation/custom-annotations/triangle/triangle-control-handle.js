(function(exports) {
  function TriangleControlHandleFactory(Annotations, WVMathNamespace) {
    class TriangleControlHandle extends Annotations.ControlHandle {
      constructor(annotation, index) {
        super();
        this.annotation = annotation;
        // set the index of this control handle so that we know which vertex it corresponds to
        this.index = index;
      }
      // returns a rect that should represent the control handle's position and size
      getDimensions(annotation, selectionBox, zoom) {
        let x = annotation.vertices[this.index].x;
        let y = annotation.vertices[this.index].y;
        // account for zoom level
        const width = Annotations.ControlHandle.handleWidth / zoom;
        const height = Annotations.ControlHandle.handleHeight / zoom;

        // adjust for the control handle's own width and height
        x -= width * 0.5;
        y -= height * 0.5;
        return new WVMathNamespace.Rect(x, y, x + width, y + height);
      }
      // this function is called when the control handle is dragged
      move(annotation, deltaX, deltaY) {
        annotation.vertices[this.index].x += deltaX;
        annotation.vertices[this.index].y += deltaY;

        // recalculate the X, Y, width and height of the annotation
        let minX = Number.MAX_VALUE;
        let maxX = -Number.MAX_VALUE;
        let minY = Number.MAX_VALUE;
        let maxY = -Number.MAX_VALUE;
        for (let i = 0; i < annotation.vertices.length; ++i) {
          const vertex = annotation.vertices[i];
          minX = Math.min(minX, vertex.x);
          maxX = Math.max(maxX, vertex.x);
          minY = Math.min(minY, vertex.y);
          maxY = Math.max(maxY, vertex.y);
        }

        const rect = new Annotations.Rect(minX, minY, maxX, maxY);
        annotation.setRect(rect);
        // return true if redraw is needed
        return true;
      }
    }
    return TriangleControlHandle;
  }

  exports.TriangleControlHandleFactory = {
    initialize: TriangleControlHandleFactory,
  };
})(window);
