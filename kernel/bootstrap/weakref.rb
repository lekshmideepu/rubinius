# -*- encoding: us-ascii -*-

class WeakRef

  class RefError < RuntimeError; end

  def self.new
    Rubinius.primitive :weakref_new
    raise PrimitiveFailure, "WeakRef.new failed"
  end

  def __setobj__(obj)
    Rubinius.primitive :weakref_set_object
    raise PrimitiveFailure, "WeakRef#__setobj__ failed"
  end

  def __object__
    Rubinius.primitive :weakref_object
    raise PrimitiveFailure, "WeakRef#__object__ failed"
  end

  def __getobj__
    obj = __object__()
    raise RefError, "Object has been collected as garbage" unless obj
    return obj
  end

  def weakref_alive?
    !!__object__
  end

  def method_missing(method, *args, &block)
    target = __getobj__
    if target.respond_to?(method)
      target.__send__(method, *args, &block)
    else
      super(method, *args, &block)
    end
  end
end
