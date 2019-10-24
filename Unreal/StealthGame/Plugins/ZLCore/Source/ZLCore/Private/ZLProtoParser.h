#pragma once

#include "CoreMinimal.h"
#include "ZLStructs.h"

#pragma warning(push)
#pragma warning(disable : 4647)
#pragma warning(disable : 4668)
#include "proto/controller/Input.pb.h"
#include "proto/GameSpaceCalibration.pb.h"
#include "proto/GameState.pb.h"
#include "proto/player/Profile.pb.h"
#include "proto/player/Stats.pb.h"
#include "proto/Session.pb.h"
#include "proto/Site.pb.h"
#include "proto/GameMasterView.pb.h"
#include "proto/Networking/Transmission.pb.h"
#include "proto/ProfileMaps.pb.h"
#include "proto/Site.pb.h"
#include "proto/player/PlayerTrackingData.pb.h"
#include "proto/Quaternion.pb.h"
#include "proto/Vector3.pb.h"



#pragma warning(pop)

namespace zl
{
	zl::proto::player::StatsMap ToProto(FZLPlayerStatsMap data)
	{
		zl::proto::player::StatsMap Value;

		for (const auto& pair : data.PlayerStats)
		{
			zl::proto::player::Stats Stats;

			Stats.set_score(pair.Value.Score);

			for (const auto& areaPair : pair.Value.AreaStats)
			{
				zl::proto::player::AreaStats AreaStats;

				for (const auto& statsPair : areaPair.Value.Stats)
				{
					(*AreaStats.mutable_stats())[TCHAR_TO_ANSI(*statsPair.Key)] = statsPair.Value;
				}

				(*Stats.mutable_areastats())[TCHAR_TO_ANSI(*areaPair.Key)] = AreaStats;
			}

			(*Value.mutable_playerstats())[TCHAR_TO_ANSI(*pair.Key)] = Stats;
		}

		return Value;
	}

	zl::proto::EGameState ToProto(EZLGameState state)
	{
		switch (state)
		{
		case EZLGameState::Start:
			return proto::EGameState::START;

		case EZLGameState::Paused:
			return proto::EGameState::PAUSED;

		case EZLGameState::Running:
			return proto::EGameState::RUNNING;

		case EZLGameState::End:
			return proto::EGameState::END;
		}

		return proto::EGameState::START;
	}

	zl::proto::player::PlayerTrackingData ToProto(FZLPlayerTrackingData trackingData)
	{
		zl::proto::player::PlayerTrackingData Value;	
			
		// Converting axis names and units from unreal to launcher here:
		// Vector3: XYZ -> YZX / 100
		// Quaternion: XYZW -> YXZW

		Value.mutable_arenaheadposition()->set_x(trackingData.ArenaHeadPosition.Y / 100);
		Value.mutable_arenaheadposition()->set_y(trackingData.ArenaHeadPosition.Z / 100);
		Value.mutable_arenaheadposition()->set_z(trackingData.ArenaHeadPosition.X / 100);

		Value.mutable_arenaheadorientation()->set_x(trackingData.ArenaHeadOrientation.Y);
		Value.mutable_arenaheadorientation()->set_y(trackingData.ArenaHeadOrientation.X);
		Value.mutable_arenaheadorientation()->set_z(trackingData.ArenaHeadOrientation.Z);
		Value.mutable_arenaheadorientation()->set_w(trackingData.ArenaHeadOrientation.W);

		Value.mutable_trackingheadposition()->set_x(trackingData.TrackingHeadPosition.Y / 100);
		Value.mutable_trackingheadposition()->set_y(trackingData.TrackingHeadPosition.Z / 100);
		Value.mutable_trackingheadposition()->set_z(trackingData.TrackingHeadPosition.X / 100);

		Value.mutable_trackingheadorientation()->set_x(trackingData.TrackingHeadOrientation.Y);
		Value.mutable_trackingheadorientation()->set_y(trackingData.TrackingHeadOrientation.X);
		Value.mutable_trackingheadorientation()->set_z(trackingData.TrackingHeadOrientation.Z);
		Value.mutable_trackingheadorientation()->set_w(trackingData.TrackingHeadOrientation.W);

		for (auto ctrl : trackingData.TrackedControllers)
		{
			Value.add_trackedcontrollers(ctrl);
		}
		
		return Value;
	}
	
}
