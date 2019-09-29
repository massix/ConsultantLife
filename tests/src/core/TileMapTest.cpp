#include <core/TileMap.h>
#include <gtest/gtest.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class TileMapTest : public testing::Test {
protected:
	TileMapTest() {
		al_init();
		al_init_image_addon();
		t = new cl::core::TileMap("resources/sophia_small.json");
		t->load();

	}

	virtual ~TileMapTest() {
		delete t;
	}

	cl::core::TileMap* t;
};

TEST_F(TileMapTest, testLayersAndTiles) {
	EXPECT_EQ(t->getLayers().size(), 2);
	EXPECT_EQ(t->getTileSets().size(), 1);
}

TEST_F(TileMapTest, testLayersComposition) {
	cl::core::Layer const& baseLayer = t->getLayers()[0];
	EXPECT_EQ(baseLayer.getName(), "base");

	cl::core::Layer const& firstLayer = t->getLayers()[1];
	EXPECT_EQ(firstLayer.getName(), "first");
}

TEST_F(TileMapTest, testLayerDetails) {
	cl::core::Layer const& baseLayer = t->getLayers().front();

	// The base layer normally should have all the bits set
	EXPECT_EQ(baseLayer.getWidth(), 30);
	EXPECT_EQ(baseLayer.getHeight(), 30);
	EXPECT_EQ(baseLayer.getData().size(), baseLayer.getWidth() * baseLayer.getHeight());
	EXPECT_TRUE(baseLayer.isVisible());

	// Check the first bits of the first layer
	cl::core::Data const& baseData = baseLayer.getData();
	EXPECT_EQ(baseData[0], 10);
	EXPECT_EQ(baseData[5], 462);

	// Check the last bits
	EXPECT_EQ(baseData[baseData.size() - 1], 29);
	EXPECT_EQ(baseData[baseData.size() - 8], 464);
}

TEST_F(TileMapTest, testTileSet) {
	cl::core::TileSet const& tileSet = t->getTileSets().front();

	EXPECT_EQ(tileSet.getImageFile(), "resources/tilemap.png");
	EXPECT_EQ(tileSet.getFirstGid(), 1);
	EXPECT_EQ(tileSet.getTilesCount(), 486);
	EXPECT_EQ(tileSet.getTileHeight(), 16);
	EXPECT_EQ(tileSet.getTileWidth(), 16);
}

TEST_F(TileMapTest, testBasicDetails) {
	EXPECT_EQ(t->getTileHeight(), 16);
	EXPECT_EQ(t->getTileWidth(), 16);
}
