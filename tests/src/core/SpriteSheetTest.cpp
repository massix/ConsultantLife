#include <core/SpriteSheet.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <gtest/gtest.h>

class SpriteSheetTest : public testing::Test {
protected:
	SpriteSheetTest() {
		al_init();
		al_init_image_addon();
	}

	void SetUp() override {
		spriteSheet = new cl::core::SpriteSheet("resources/pink_consultant.json");
		spriteSheet->load();

	}

	void TearDown() override {
		if (spriteSheet != nullptr) {
			delete spriteSheet;
		}
	}

	cl::core::SpriteSheet* spriteSheet;
};

TEST_F(SpriteSheetTest, testLoadFile) {
	EXPECT_EQ(spriteSheet->getName(), "Pink Consultant");
	EXPECT_EQ(spriteSheet->getDescription(), "Spritesheet for a consultant with pink hair");
	EXPECT_EQ(spriteSheet->getFormat(), "spritesheet");
}

TEST_F(SpriteSheetTest, testParameters) {
	EXPECT_EQ(spriteSheet->getParameters()->getSplit(), "line");
	EXPECT_EQ(spriteSheet->getParameters()->getXDistance(), 64);
	EXPECT_EQ(spriteSheet->getParameters()->getNature(), "animations");
	EXPECT_EQ(spriteSheet->getParameters()->getAnimations().size(), 21);
}

TEST_F(SpriteSheetTest, testAnimation) {
	cl::core::Animation const& animation = spriteSheet->getAnimation("walk_down");
	EXPECT_EQ(animation.getFrames(), 9);
	EXPECT_EQ(animation.getIndex(), 10);
	EXPECT_EQ(animation.getName(), "walk_down");
}
