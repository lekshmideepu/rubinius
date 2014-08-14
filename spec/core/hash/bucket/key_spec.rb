require File.expand_path('../../../../spec_helper', __FILE__)

with_feature :hash_bucket do
  describe "Hash::Bucket#key" do
    it "returns the key object" do
      Hash::Bucket.new(1, 1.hash, 2).key.should == 1
    end
  end

  describe "Hash::Bucket#key=" do
    it "sets the key object" do
      b = Hash::Bucket.new 1, 2, 3
      b.key = 2
      b.key.should == 2
    end
  end
end
