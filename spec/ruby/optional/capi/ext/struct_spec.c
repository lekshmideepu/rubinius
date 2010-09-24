#include "ruby.h"
#include "intern.h"
#include "rubyspec.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_RB_STRUCT_AREF
static VALUE struct_spec_rb_struct_aref(VALUE self, VALUE st, VALUE key) {
  return rb_struct_aref(st, key);
}
#endif

#ifdef HAVE_RB_STRUCT_ASET
static VALUE struct_spec_rb_struct_aset(VALUE self, VALUE st, VALUE key, VALUE value) {
  return rb_struct_aset(st, key, value);
}
#endif

#ifdef HAVE_RB_STRUCT_DEFINE
/* Only allow setting three attributes, should be sufficient for testing. */
static VALUE struct_spec_struct_define(VALUE self, VALUE name,
  VALUE attr1, VALUE attr2, VALUE attr3) {

  const char *a1 = StringValuePtr(attr1);
  const char *a2 = StringValuePtr(attr2);
  const char *a3 = StringValuePtr(attr3);
  char *nm = NULL;

  if (name != Qnil) nm = StringValuePtr(name);

  return rb_struct_define(nm, a1, a2, a3, NULL);
}
#endif

void Init_struct_spec() {
  VALUE cls;
  cls = rb_define_class("CApiStructSpecs", rb_cObject);

#ifdef HAVE_RB_STRUCT_AREF
  rb_define_method(cls, "rb_struct_aref", struct_spec_rb_struct_aref, 2);
#endif

#ifdef HAVE_RB_STRUCT_ASET
  rb_define_method(cls, "rb_struct_aset", struct_spec_rb_struct_aset, 3);
#endif

#ifdef HAVE_RB_STRUCT_DEFINE
  rb_define_method(cls, "rb_struct_define", struct_spec_struct_define, 4);
#endif
}

#ifdef __cplusplus
}
#endif
