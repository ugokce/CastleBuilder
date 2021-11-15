#pragma once

enum class PriceType
{
	Gold,
	Silver,
	Diamond,
	None
};

struct Price
{
	unsigned int value = 0;
	PriceType type = PriceType::None;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(value), CEREAL_NVP(type));
	}
};