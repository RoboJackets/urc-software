(function(exports) {
  function TriangleCreateToolFactory(Tools, TriangleAnnotation) {
    class TriangleCreateTool extends Tools.GenericAnnotationCreateTool {
      constructor(docViewer) {
        // TriangleAnnotation is the class (function) for our annotation we defined previously
        super(docViewer, TriangleAnnotation);
      }

      mouseMove(e) {
        // call the parent mouseMove first
        super.mouseMove(e);
        if (this.annotation) {
          // set the vertices relative to the annotation width and height
          this.annotation.vertices[0].x = this.annotation.X + this.annotation.Width / 2;
          this.annotation.vertices[0].y = this.annotation.Y;
          this.annotation.vertices[1].x = this.annotation.X + this.annotation.Width;
          this.annotation.vertices[1].y = this.annotation.Y + this.annotation.Height;
          this.annotation.vertices[2].x = this.annotation.X;
          this.annotation.vertices[2].y = this.annotation.Y + this.annotation.Height;

          // update the annotation appearance
          this.documentViewer.getAnnotationManager().redrawAnnotation(this.annotation);
        }
      }
    }

    return TriangleCreateTool;
  }

  exports.TriangleCreateToolFactory = {
    initialize: TriangleCreateToolFactory,
  };
})(window);
