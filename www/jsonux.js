function JsonUx(dom, json) {
  this.dom = dom;
  this.json = json;
}

JsonUx.prototype.build = function() {
  var elem = $("<"+this.json.type+"/>");

  if (this.json.id) elem.attr("id", this.json.id);
  if (this.json.class) elem.addClass(this.json.class);
  if (this.json.html) elem.html(this.json.html);
  if (this.json.js) eval(this.json.js);
  if (this.json.src) elem.attr("src", this.json.src);

  this.dom = $(this.dom).append(elem);

  if (this.json.items) {
    (this.json.items).forEach(function(entry) {
      var newElem = new JsonUx(elem, entry);
      newElem.build();
    }, this);
  }
};
