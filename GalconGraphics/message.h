/// @file message.h
/// @brief messages uses to exchange information between classes
/// @author: Kulykivsky Vitaliy
/// @date: 01-Jun-2011

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QVector>
#include <QPair>
#include <QSize>
#include <QPoint>
#include <QString>

namespace MessageDecl
{
    struct CPlanetParameters
    {
        int m_planetId; ///< planet id
        int m_playerId; ///< owner Id
        QPoint m_pos; ///< planet position
        int m_radius; ///< planet radius
        int m_numFleet; ///< fleet's count on planet
        CPlanetParameters()
        {
        }
        /// @brief ctor
        CPlanetParameters(int i_planetId, int i_playerId,
                          QPoint i_pos, int i_radius, int i_numFleet) : m_planetId(i_planetId),
                                m_playerId(i_playerId), m_pos(i_pos), m_radius(i_radius),
                                m_numFleet(i_numFleet)
        {
        }
    };
    struct CSheetParameters
    {
        int m_startPlanetId;
        int m_destinationPlanetId;
        int m_sheetId; ///< id
        int m_playerId; ///< owner Id
        int m_numFleet; ///< fleet's count on planet
        int m_percent;
        CSheetParameters()
        {
        }
        /// @brief ctor
        CSheetParameters(int i_sheetId, int i_playerId, int i_planetStartId, int i_planetDestinationId,
                         int i_numFleet, int i_percent) :
                          m_startPlanetId(i_planetStartId), m_destinationPlanetId(i_planetDestinationId),
                            m_sheetId(i_sheetId),
                            m_playerId(i_playerId), m_numFleet(i_numFleet), m_percent(i_percent)
        {
        }
    };
    /// @class CMessage
    /// @brief it used for exchanging infirmations between classes
    class CMessage
    {
    public:
        enum EType
        {
            eError = 1,
            eInit,
            eUserId,
            eStep,
            eTimeToSTart,
            eState,
            eFinish,
            eConnect
        };
        virtual QString GetData()
        {
            return QString("");
        }
        EType m_type; ///< message type
        /// @brief default ctor
        CMessage(){}
        CMessage(EType i_type) : m_type(i_type)
        {
        };
    };// CMessage

    /// @class CInitMessage
    /// @brief used for exchanging infirmation when server send initial parameters
    /// @collab it inherited from CMessage
    class CInitMessage : public CMessage
    {
    public:
        QSize m_szMap; ///< map size
        int m_planetSheetIncreaseSpeed; ///< increase speed
        int m_sheetFlySpeed; ///< flight speed
        QVector<CPlanetParameters> m_planets;
        QVector< QPair<int, QString> > m_players;//pair<id, nick>

        /// @brief default ctor
        CInitMessage(EType i_type) : CMessage(i_type)
        {
        };

        /// @brief ctor
        /// @param i_size in, size of map
        /// @param i_planetIncreaseSpeed in, increase planet's fleet count
        /// @param i_shipSpeed in, sheet's fly speed
        CInitMessage(EType i_type, const QSize& i_size, const int i_planetIncreaseSpeed,
                     const int i_sheetSpeed) :
                        CMessage(i_type), m_szMap(i_size),
                        m_planetSheetIncreaseSpeed(i_planetIncreaseSpeed),
                        m_sheetFlySpeed(i_sheetSpeed)
        {
        }



        CInitMessage(EType i_type, const QSize& i_size, const int i_planetIncreaseSpeed,
                     const int i_sheetSpeed,QVector<CPlanetParameters> plan, QVector<QPair<int, QString> > players) :
                        CMessage(i_type), m_szMap(i_size),
                        m_planetSheetIncreaseSpeed(i_planetIncreaseSpeed),
                        m_sheetFlySpeed(i_sheetSpeed)
        {
            m_planets.clear();
            m_planets.resize(plan.size());
            int i;
            for(i=0; i<plan.size(); i++)
                m_planets[i]=plan[i];

            m_players.clear();
            m_players.resize(players.size());
            for(i=0; i<players.size(); i++)
                m_players[i]=players[i];
        }

        void AddPlanet(CPlanetParameters  i_planet)//int i_panetId, int i_playerId,
                       // QPoint i_pos, int i_radius, int i_numFleet)
        {
            //CPlanetParameters tmp(i_panetId, i_playerId, i_pos, i_radius, i_numFleet);
            m_planets.push_back(i_planet);
        }
        void AddPlayer(int i_playerId, QString i_nick)
        {
            m_players.push_back(QPair<int, QString>(i_playerId, i_nick));
        }
    };

    /// @class CUserIdMessage
    /// @brief used for delivering PlayerId from server to CMap
    /// @collab it inherited from CMessage
    class CIntMessage : public CMessage
    {
    public:
        /// @brief default ctor
        CIntMessage(EType i_type) : CMessage(i_type)
        {
        };


        /// @brief ctor
        /// @param i_value in, value
        CIntMessage(EType i_type, const int i_value) : CMessage(i_type), m_value(i_value)
        {
        }

        int m_value; ///< value
    };

    /// @class CErrorMessage
    /// @brief used for delivering error information
    /// @collab it inherited from CMessage
    class CStringMessage : public CMessage
    {
    public:
        /// @brief default ctor
        CStringMessage(EType i_type) : CMessage(i_type)
        {
        };

        /// @brief ctor
        /// @param i_str in, error message
        CStringMessage(EType i_type, const QString& i_str) : CMessage(i_type), m_str(i_str)
        {
        }
        QString GetData()
        {
            return m_str;
        }
        QString m_str; ///< error message
    };

    /// @brief command send message
    class CStepMessage : public CMessage
    {
    public:
        QVector<int> m_planetIds;
        int m_percent;
        int m_destinationPlanetId;
    public:
        CStepMessage(EType i_type) : CMessage(i_type)
        {
        };
        CStepMessage(EType i_type, int perc) : CMessage(i_type), m_percent(perc)
        {
        };
        void AddPlanet(int i_id)
        {
            m_planetIds.push_back(i_id);
        }
        void SetPercent(int i_percent)
        {
            m_percent = i_percent;
        }
        void SetDestinationPlanet(int i_planetId)
        {
            m_destinationPlanetId = i_planetId;
        }
    };
    class CStateMessage : public CMessage
    {
    public:
        QVector<CPlanetParameters> m_planets;
        QVector<CSheetParameters> m_sheets;
    public:
        CStateMessage(){}
        CStateMessage(EType i_type) : CMessage(i_type)
        {
        };
        CStateMessage(QVector<CPlanetParameters> planets, QVector<CSheetParameters> fleets)
        {
            m_planets=planets;
            m_sheets=fleets;
        }

        void AddPlanet(int i_planetId, int i_playerId, int i_numSheeps)
        {
            m_planets.push_back(CPlanetParameters(i_planetId, i_playerId, QPoint(0, 0), 0, i_numSheeps));
        }
        void AddFleep(int i_sheetId, int i_playerId, int i_planetStartId, int i_planetEndId,
                      int i_numSheeps, int i_percent)
        {
            m_sheets.push_back(CSheetParameters(i_sheetId, i_playerId, i_planetStartId, i_planetEndId,
                                                   i_numSheeps, i_percent));
        }
            };
}; // MessageDecl

#endif // MESSAGE_H
