(function(exports) {
  function TriangleSelectionModelFactory(Annotations, Math) {
    class TriangleSelectionModel extends Annotations.SelectionModel {
      constructor(annotation, canModify) {
        super(annotation, canModify);
        if (canModify) {
          const TriangleControlHandle = exports.TriangleControlHandleFactory.initialize(Annotations, Math);
          const controlHandles = this.getControlHandles();
          // pass the vertex index to each control handle
          controlHandles.push(new TriangleControlHandle(annotation, 0));
          controlHandles.push(new TriangleControlHandle(annotation, 1));
          controlHandles.push(new TriangleControlHandle(annotation, 2));
        }
      }
      // ...
      // changes how we draw the selection outline
      drawSelectionOutline(ctx, annotation, zoom) {
        // adjust for zoom
        if (typeof zoom !== 'undefined') {
          ctx.lineWidth = Annotations.SelectionModel.selectionOutlineThickness / zoom;
        } else {
          ctx.lineWidth = Annotations.SelectionModel.selectionOutlineThickness;
        }

        // changes the selection outline color if the user doesn't have permission to modify this annotation
        if (this.canModify()) {
          ctx.strokeStyle = Annotations.SelectionModel.defaultSelectionOutlineColor.toString();
        } else {
          ctx.strokeStyle = Annotations.SelectionModel.defaultNoPermissionSelectionOutlineColor.toString();
        }

        ctx.beginPath();
        ctx.moveTo(annotation.vertices[0].x, annotation.vertices[0].y);
        ctx.lineTo(annotation.vertices[1].x, annotation.vertices[1].y);
        ctx.lineTo(annotation.vertices[2].x, annotation.vertices[2].y);
        ctx.closePath();
        ctx.stroke();

        // draw a dashed line around the triangle
        const dashUnit = Annotations.SelectionModel.selectionOutlineDashSize / zoom;
        const sequence = [dashUnit, dashUnit];
        ctx.setLineDash(sequence);
        ctx.strokeStyle = 'rgb(255, 255, 255)';
        ctx.stroke();
      }
      // change the selection testing to match the shape of the triangle
      testSelection(annotation, x, y, pageMatrix) {
        // the canvas visibility test will only select the annotation
        // if a user clicks exactly on it as opposed to the rectangular bounding box
        return Annotations.SelectionAlgorithm.canvasVisibilityTest(annotation, x, y, pageMatrix);
      }
    }
    return TriangleSelectionModel;
  }

  exports.TriangleSelectionModelFactory = {
    initialize: TriangleSelectionModelFactory,
  };
})(window);
