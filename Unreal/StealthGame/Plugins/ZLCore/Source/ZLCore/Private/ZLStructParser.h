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
#include "proto/BackpackStatus.pb.h"
#include "proto/launcher/LauncherInfo.pb.h"
#include "proto/MapBounds.pb.h"

#pragma warning(pop)

namespace zl
{
	FZLBlasterInput ToStruct(const zl::proto::controller::Input& data)
	{
		FZLBlasterInput Value;

		//Grab the inputs out of the  bit field
		auto InputBitfield = data.inputs();

		Value.TriggerPulled = (InputBitfield & proto::controller::Input::TRIGGER);
		Value.SideButtonPressed = (InputBitfield & proto::controller::Input::SIDE_BUTTON);
		Value.BottomButtonPressed = (InputBitfield & proto::controller::Input::BOTTOM_BUTTON);

		Value.PumpState = EBlasterPumpState::PUMP_IDLE;

		if (InputBitfield & proto::controller::Input::PUMP_FORWARD)
		{
			Value.PumpState = EBlasterPumpState::PUMP_FORWARD;
		}

		if (InputBitfield & proto::controller::Input::PUMP_BACK)
		{
			Value.PumpState = EBlasterPumpState::PUMP_BACK;
		}
	
		return Value;
	}

	FZLProfile ToStruct(const zl::proto::player::Profile& data)
	{
		FZLProfile Value;

		Value.FirstName = FString(data.firstname().data());
		Value.LastName = FString(data.lastname().data());
		Value.DisplayName = FString(data.displayname().data());
		Value.FallbackName = FString(data.fallbackname().data());
		Value.Height = data.height();
		Value.bLeftHanded = data.blefthanded();
		Value.Gender = data.gender() == proto::player::Profile::FEMALE ? EZLGender::Female : data.gender() == proto::player::Profile::MALE ? EZLGender::Male : EZLGender::Other;
		// TODO: language to string
		// Value.Language = FString(data.language());

		return Value;
	}

	FZLSession ToStruct(const zl::proto::Session& data)
	{
		FZLSession Value;

		for (const auto& pair : data.profilesbyprofileid())
		{
			const proto::player::Profile& profile = pair.second;

			Value.ProfilesByProfileId.Add(pair.first, ToStruct(profile));
		}

		return Value;
	}

	FZLObstacleBounds ToStruct(const zl::proto::ObstacleBounds& data)
	{
		FZLObstacleBounds Value;
		
		for (const auto& coord : data.vertices())
		{
			Value.Vertices.Add(FVector2D(coord.y(), coord.x())); // switch x and y components
		}

		return Value;
	}

	FZLMapBounds ToStruct(const zl::proto::MapBounds& data)
	{
		FZLMapBounds Value;
		
		for (const auto& coord : data.boundaryvertices())
		{
			Value.BoundaryVertices.Add(FVector2D(coord.y(), coord.x())); // switch x and y components
		}

		for (const auto& obstacle : data.obstacles())
		{
			Value.Obstacles.Add(zl::ToStruct(obstacle));
		}

		return Value;
	}

	FZLSite ToStruct(const zl::proto::Site& data)
	{
		FZLSite Value;
		Value.SiteId = data.siteid();
		Value.ContentMap = (EContentMap) data.contentmap();

		return Value;
	}

	FZLLauncherInfo ToStruct(const zl::proto::launcher::LauncherInfo& data)
	{
		FZLLauncherInfo Value;
		switch (data.mode())
		{
			case proto::EAppMode::SERVER:
			{
				Value.Mode = ELauncherMode::SERVER;
				break;
			}
			case proto::EAppMode::CLIENT:
			{
				Value.Mode = ELauncherMode::BACKPACK;
				break;
			}
			case proto::EAppMode::SPECTATOR:
			{
				Value.Mode = ELauncherMode::SPECTATOR;
				break;
			}
			case proto::EAppMode::GAME_MASTER:
			{
				Value.Mode = ELauncherMode::GAME_MASTER;
				break;
			}
			default:
				Value.Mode = ELauncherMode::UNKNOWN;
				break;
		}

		return Value;
	}

	FZLBackpackStatus ToStruct(const zl::proto::BackpackStatus& data)
	{
		FZLBackpackStatus Value;
		Value.TrackingOk = data.trackingok();
		Value.IsControllerHybrid = data.iscontrollerhybrid();

		FVector leftAngles;
		FVector leftTranslation;

		FVector rightAngles;
		FVector rightTranslation;
				
		leftAngles.X = -data.leftcontrollereulerangleoffset().z();
		leftAngles.Y = -data.leftcontrollereulerangleoffset().x();
		leftAngles.Z = data.leftcontrollereulerangleoffset().y();

		rightAngles.X = -data.rightcontrollereulerangleoffset().z();
		rightAngles.Y = -data.rightcontrollereulerangleoffset().x();
		rightAngles.Z = data.rightcontrollereulerangleoffset().y();
		
		// Vector3:  XYZ -> ZXY * 100
		leftTranslation.X = data.leftcontrollertranslationoffset().z() * 100;
		leftTranslation.Y = data.leftcontrollertranslationoffset().x() * 100;
		leftTranslation.Z = data.leftcontrollertranslationoffset().y() * 100;

		rightTranslation.X = data.rightcontrollertranslationoffset().z() * 100;
		rightTranslation.Y = data.rightcontrollertranslationoffset().x() * 100;
		rightTranslation.Z = data.rightcontrollertranslationoffset().y() * 100;
		
		Value.LeftControllerRotationOffset = FQuat::MakeFromEuler(leftAngles);
		Value.RightControllerRotationOffset = FQuat::MakeFromEuler(rightAngles);

		Value.LeftControllerTranslationOffset = leftTranslation;
		Value.RightControllerTranslationOffset = rightTranslation;

		return Value;
	}

	FZLGameMasterRow ToStruct(const zl::proto::GameMasterRow& data)
	{
		FZLGameMasterRow Value;

		for (const auto& clientIp : data.viewclientips())
		{
			Value.ViewIps.Add(FString(clientIp.c_str()));
		}

		return Value;
	}

	FZLGameMasterView ToStruct(const zl::proto::GameMasterView& data)
	{
		FZLGameMasterView Value;
		
		for (const auto& row : data.rows())
		{
			Value.Rows.Add(zl::ToStruct(row));
		}

		return Value;
	}

	FZLPlayerProfileMaps ToStruct(const zl::proto::ProfileMaps& data)
	{
		FZLPlayerProfileMaps Value;

		for (const auto& pair : data.idsbyclientip())
		{
			Value.IdsByClientIp.Add(FString(pair.first.c_str()), pair.second);
		}

		return Value;
	}

	FZLPlayerStatsMap ToStruct(const zl::proto::player::StatsMap& data)
	{
		FZLPlayerStatsMap Value;

		for (const auto& pair : data.playerstats())
		{
			FZLPlayerStats Stats;

			Stats.Score = pair.second.score();

			for (const auto& areaPair : pair.second.areastats())
			{
				FZLPlayerAreaStats AreaStats;

				for (const auto& statPair : areaPair.second.stats())
				{
					AreaStats.Stats.Add(FString(statPair.first.c_str()), statPair.second);
				}

				Stats.AreaStats.Add(FString(areaPair.first.c_str()), AreaStats);
			}

			Value.PlayerStats.Add(FString(pair.first.c_str()), Stats);
		}

		return Value;
	}

	EZLGameState ToStruct(const zl::proto::GameState& data)
	{
		switch (data.state())
		{
		case proto::EGameState::START:
			return EZLGameState::Start;

		case proto::EGameState::PAUSED:
			return EZLGameState::Paused;

		case proto::EGameState::RUNNING:
			return EZLGameState::Running;

		case proto::EGameState::END:
			return EZLGameState::End;
		}

		return EZLGameState::Start;
	}
}
