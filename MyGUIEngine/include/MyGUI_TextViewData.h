/*!
	@file
	@author		Albert Semenov
	@date		09/2009
*/
#ifndef __MYGUI_TEXT_VIEW_DATA_H__
#define __MYGUI_TEXT_VIEW_DATA_H__

#include "MyGUI_Prerequest.h"

namespace MyGUI
{

	class CharInfo
	{
	public:
		CharInfo() :
			mIsColour(false)
		{
			mMetrics.mWidth = 0.0f;
			mMetrics.mHeight = 0.0f;
			mMetrics.mAdvance = 0.0f;
			mMetrics.mBearingX = 0.0f;
			mMetrics.mBearingY = 0.0f;
		}

		CharInfo(
			const FloatRect& _rect,
            ITexture* _texture,
			float _width,
			float _height,
			float _advance,
			float _bearingX,
			float _bearingY) :
			mIsColour(false),
            mTexture(_texture),
			mUVRect(_rect)
		{
			mMetrics.mWidth = _width;
			mMetrics.mHeight = _height;
			mMetrics.mAdvance = _advance;
			mMetrics.mBearingX = _bearingX;
			mMetrics.mBearingY = _bearingY;
		}

		CharInfo(uint32 _colour) :
			mIsColour(true),
			mColour(_colour)
		{ }

		bool isColour() const
		{
			return mIsColour;
		}

		float getWidth() const
		{
			return mMetrics.mWidth;
		}

		float getHeight() const
		{
			return mMetrics.mHeight;
		}

		float getAdvance() const
		{
			return mMetrics.mAdvance;
		}

		float getBearingX() const
		{
			return mMetrics.mBearingX;
		}

		float getBearingY() const
		{
			return mMetrics.mBearingY;
		}

		const FloatRect& getUVRect() const
		{
			return mUVRect;
		}

		uint32 getColour() const
		{
			return mColour;
		}

        ITexture* getTexture() const
        {
            return mTexture;
        }

	private:

		bool mIsColour;
        ITexture* mTexture;
		FloatRect mUVRect;

		struct Metrics
		{
			float mWidth;
			float mHeight;
			float mAdvance;
			float mBearingX;
			float mBearingY;
		};

		union
		{
			Metrics mMetrics;
			uint32 mColour;
		};

	};

	typedef vector<CharInfo>::type VectorCharInfo;

	struct LineInfo
	{
		LineInfo() :
			width(0),
			offset(0),
			count(0),
			autoNewLine(false)
		{
		}

		void clear()
		{
			width = 0;
			count = 0;
			simbols.clear();
			offset = 0;
			autoNewLine = false;
		}

		int width;
		int offset;
		size_t count;
		VectorCharInfo simbols;
		bool autoNewLine;
	};

	typedef vector<LineInfo>::type VectorLineInfo;

} // namespace MyGUI

#endif // __MYGUI_TEXT_VIEW_DATA_H__
