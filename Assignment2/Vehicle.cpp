#include "Vehicle.h"

namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount)
		: mMaxPassengersCount(maxPassengersCount),
		  mSize(0),
		  mCurrentCounts(0),
		  mTravelLimits(0),
		  mTravelDistance(0),
		  mTotalLimits(0)
	{
		mPassengers = new const Person * [mMaxPassengersCount];

		for (unsigned int i = 0; i < mMaxPassengersCount; i++)
		{
			mPassengers[i] = nullptr;
		}
	}

	Vehicle::Vehicle(const Vehicle& rhs)
		: mMaxPassengersCount(rhs.mMaxPassengersCount),
		  mSize(rhs.mSize),
		  mCurrentCounts(rhs.mCurrentCounts),
		  mTravelLimits(rhs.mTravelLimits),
		  mTravelDistance(rhs.mTravelDistance),
		  mTotalLimits(rhs.mTotalLimits)
	{
		mPassengers = new const Person * [mMaxPassengersCount];

		for (unsigned int i = 0; i < mSize; i++)
		{
			mPassengers[i] = static_cast<const Person*>(rhs.mPassengers[i]);
			rhs.mPassengers[i] = nullptr;
		}

		for (unsigned int i = mSize; i < mMaxPassengersCount; i++)
		{
			mPassengers[i] = nullptr;
		}
	}

	Vehicle& Vehicle::operator=(const Vehicle& rhs)
	{
		if (&rhs != this)
		{
			mMaxPassengersCount = rhs.mMaxPassengersCount;
			mSize = rhs.mSize;
			mCurrentCounts = rhs.mCurrentCounts;
			mTravelLimits = rhs.mTravelLimits;
			mTravelDistance = rhs.mTravelDistance;
			mTotalLimits = rhs.mTotalLimits;

			for (unsigned int i = 0; i < mMaxPassengersCount; i++)
			{
				if (mPassengers != nullptr)
				{
					delete mPassengers[i];
				}
			}

			delete[] mPassengers;

			mPassengers = new const Person * [mMaxPassengersCount];

			for (unsigned int i = 0; i < mSize; i++)
			{
				mPassengers[i] = rhs.mPassengers[i];
				rhs.mPassengers[i] = nullptr;
			}

			for (unsigned int i = mSize; i < mMaxPassengersCount; i++)
			{
				mPassengers[i] = nullptr;
			}
		}

		return *this;
	}

	Vehicle::~Vehicle()
	{
		for (unsigned int i = 0; i < mMaxPassengersCount; i++)
		{
			if (mPassengers != nullptr)
			{
				delete mPassengers[i];
			}
		}

		delete[] mPassengers;
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		if (mSize >= mMaxPassengersCount || person == nullptr)
		{
			return false;
		}

		if (IsThere(person))
		{
			return false;
		}
		

		mPassengers[mSize] = person;
		mSize++;
		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (mSize < MIN_PASSENGER_NUMBER)
		{
			return false;
		}
		if (i > mSize - 1)
		{
			return false;
		}

		delete mPassengers[i];
		mPassengers[i] = nullptr;

		for (unsigned int j = i; j < mSize - 1; j++)
		{
			mPassengers[j] = mPassengers[j + 1];
		}

		for (unsigned int j = mSize - 1; j < mMaxPassengersCount; j++)
		{
			mPassengers[j] = nullptr;
		}

		mSize--;
		return true;
	}

	void Vehicle::CalculateTravelDistance()
	{
		mTravelDistance += GetMaxSpeed();
	}

	bool Vehicle::IsThere(const Person* person) const
	{
		for (unsigned int i = 0; i < mSize; i++)
		{
			if (mPassengers[i] == person)
			{
				return true;
			}
		}
		return false;
	}

	void Vehicle::MoveTo(Vehicle& rhs)
	{
		for (unsigned int i = mSize; i < mSize + rhs.GetPassengersCount(); i++)
		{
			mPassengers[i] = rhs.mPassengers[i - mSize];
			rhs.mPassengers[i - mSize] = nullptr;
		}
		mSize += rhs.mSize;
		rhs.mSize = 0;
	}

	void Vehicle::IncreaseTravelCounts()
	{
		mCurrentCounts++;

		if (mCurrentCounts == mTotalLimits)
		{
			mCurrentCounts = 0;
		}
	}

	unsigned int Vehicle::GetSumOfWeight() const
	{
		unsigned int sumOfWeight = 0;

		for (unsigned int i = 0; i < mSize; i++)
		{
			sumOfWeight += mPassengers[i]->GetWeight();
		}
		return sumOfWeight;
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return mSize;
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxPassengersCount;
	}

	unsigned int Vehicle::GetCurrentCounts() const
	{
		return mCurrentCounts;
	}

	unsigned int Vehicle::GetTravelLimits() const
	{
		return mTravelLimits;
	}

	unsigned int Vehicle::GetTravelDistance() const
	{
		return mTravelDistance;
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if (i > mSize - 1)
		{
			return nullptr;
		}

		return mPassengers[i];
	}
}