/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Pennsylvania
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "chord-message.h"
#include "ns3/log.h"


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ChordMessage");

NS_OBJECT_ENSURE_REGISTERED (ChordMessage);

ChordMessage::ChordMessage (uint8_t ttl)
{
  m_transactionId = 0;
  m_ttl = ttl;
}

ChordMessage::ChordMessage ()
{
}

ChordMessage::~ChordMessage ()
{
}

TypeId
ChordMessage::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ChordMessage")
    .SetParent<Header> ()
    .AddConstructor<ChordMessage> ()
  ;
  return tid;

}

TypeId
ChordMessage::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

void 
ChordMessage::SetMessageType (MessageType messageType)
{
  m_messageType = messageType;
}

void 
ChordMessage::SetTransactionId (uint32_t transactionId)
{
  m_transactionId = transactionId;
}

void 
ChordMessage::SetTTL (uint8_t ttl)
{
  m_ttl = ttl;
} 

ChordMessage::MessageType 
ChordMessage::GetMessageType () const
{
  return m_messageType;
}

uint32_t 
ChordMessage::GetTransactionId (void)
{
  return m_transactionId;
}

void 
ChordMessage::SetRequestorNode (Ptr<ChordNode> chordNode)
{
  m_chordNode = chordNode;
}

Ptr<ChordNode> 
ChordMessage::GetRequestorNode ()
{
  return m_chordNode;
}

uint8_t 
ChordMessage::GetTTL ()
{
  return m_ttl;
} 


uint32_t
ChordMessage::GetSerializedSize (void) const
{
  uint32_t size = sizeof (uint8_t) + sizeof (uint32_t) + sizeof(uint8_t) + m_chordNode->GetSerializedSize ();
  switch (m_messageType)
    {
    case JOIN_REQ:
      size += m_message.joinReq.GetSerializedSize ();
      break;
    case JOIN_RSP:
      size += m_message.joinRsp.GetSerializedSize ();
      break;
    case LEAVE_REQ:
      size += m_message.leaveReq.GetSerializedSize ();
      break;
    case LEAVE_RSP:
      size += m_message.leaveRsp.GetSerializedSize ();
      break;
    case STABILIZE_REQ:
      size += m_message.stabilizeReq.GetSerializedSize ();
      break;
    case STABILIZE_RSP:
      size += m_message.stabilizeRsp.GetSerializedSize ();
      break;
    case FINGER_REQ:
      size += m_message.fingerReq.GetSerializedSize ();
      break;
    case FINGER_RSP:
      size += m_message.fingerRsp.GetSerializedSize ();
      break;
    case HEARTBEAT_REQ:
      size += m_message.heartbeatReq.GetSerializedSize ();
      break;
    case HEARTBEAT_RSP:
      size += m_message.heartbeatRsp.GetSerializedSize ();
      break;
    case LOOKUP_REQ:
      size += m_message.lookupReq.GetSerializedSize ();
      break;
    case LOOKUP_RSP:
      size += m_message.lookupRsp.GetSerializedSize ();
      break;
    case TRACE_RING:
      size += m_message.traceRing.GetSerializedSize ();
      break;
    default:
      NS_ASSERT (false);
    }
  return size;
}

void
ChordMessage::Print (std::ostream &os) const
{
  os << "\n***ChordMessage Dump***\n";
  os << "Header:: \n";
  os << "MessageType: " << m_messageType << "\n";
  os << "TransactionId: " << m_transactionId << "\n";
  os << "Requestor Node: " << "\n";
  m_chordNode->Print (os);
  os << "TTL : " << (uint16_t) m_ttl << "\n";
  os << "Payload:: \n";
  switch (m_messageType)
    {
    case JOIN_REQ:
      m_message.joinReq.Print (os);
      break;
    case JOIN_RSP:
      m_message.joinRsp.Print (os);
      break;
    case LEAVE_REQ:
      m_message.leaveReq.Print (os);
      break;
    case LEAVE_RSP:
      m_message.leaveRsp.Print (os);
      break;
    case STABILIZE_REQ:
      m_message.stabilizeReq.Print (os);
      break;
    case STABILIZE_RSP:
      m_message.stabilizeRsp.Print (os);
      break;
    case FINGER_REQ:
      m_message.fingerReq.Print (os);
      break;
    case FINGER_RSP:
      m_message.fingerRsp.Print (os);
      break;
    case HEARTBEAT_REQ:
      m_message.heartbeatReq.Print (os);
      break;
    case HEARTBEAT_RSP:
      m_message.heartbeatRsp.Print (os);
      break;
    case LOOKUP_REQ:
      m_message.lookupReq.Print (os);
      break;
    case LOOKUP_RSP:
      m_message.lookupRsp.Print (os);
      break;
    case TRACE_RING:
      m_message.traceRing.Print (os);
      break;
    default:
      break;
    }
  os << "\n***End Of Message***\n";
}

void
ChordMessage::Serialize (Buffer::Iterator start) const
{
  Buffer::Iterator i = start;
  i.WriteU8 (m_messageType);
  i.WriteU8  (m_ttl);
  i.WriteHtonU32 (m_transactionId);
  m_chordNode->Serialize (i);
  switch (m_messageType)
    {
    case JOIN_REQ:
      m_message.joinReq.Serialize (i);
      break;
    case JOIN_RSP:
      m_message.joinRsp.Serialize (i);
      break;
    case LEAVE_REQ:
      m_message.leaveReq.Serialize (i);
      break;
    case LEAVE_RSP:
      m_message.leaveRsp.Serialize (i);
      break;
    case STABILIZE_REQ:
      m_message.stabilizeReq.Serialize (i);
      break;
    case STABILIZE_RSP:
      m_message.stabilizeRsp.Serialize (i);
      break;
    case FINGER_REQ:
      m_message.fingerReq.Serialize (i);
      break;
    case FINGER_RSP:
      m_message.fingerRsp.Serialize (i);
      break;
    case HEARTBEAT_REQ:
      m_message.heartbeatReq.Serialize (i);
      break;
    case HEARTBEAT_RSP:
      m_message.heartbeatRsp.Serialize (i);
      break;
    case LOOKUP_REQ:
      m_message.lookupReq.Serialize (i);
      break;
    case LOOKUP_RSP:
      m_message.lookupRsp.Serialize (i);
      break;
    case TRACE_RING:
      m_message.traceRing.Serialize (i);
      break;
    default:
      NS_ASSERT (false);
    }
}

uint32_t
ChordMessage::Deserialize (Buffer::Iterator start)
{
  uint32_t size;
  Buffer::Iterator i = start;
  m_messageType = (MessageType) i.ReadU8 ();
  m_ttl = i.ReadU8 ();
  m_transactionId = i.ReadNtohU32 ();
  m_chordNode = Create<ChordNode> ();
  m_chordNode->Deserialize (i);
  size = sizeof (uint8_t) + sizeof (uint32_t) + sizeof(uint8_t) + m_chordNode->GetSerializedSize ();

  switch (m_messageType)
    {
    case JOIN_REQ:
      size += m_message.joinReq.Deserialize (i);
      break;
    case JOIN_RSP:
      size += m_message.joinRsp.Deserialize (i);
      break;
    case LEAVE_REQ:
      size += m_message.leaveReq.Deserialize (i);
      break;
    case LEAVE_RSP:
      size += m_message.leaveRsp.Deserialize (i);
      break;
    case STABILIZE_REQ:
      size += m_message.stabilizeReq.Deserialize (i);
      break;
    case STABILIZE_RSP:
      size += m_message.stabilizeRsp.Deserialize (i);
      break;
    case FINGER_REQ:
      size += m_message.fingerReq.Deserialize (i);
      break;
    case FINGER_RSP:
      size += m_message.fingerRsp.Deserialize (i);
      break;
    case HEARTBEAT_REQ:
      size += m_message.heartbeatReq.Deserialize (i);
      break;
    case HEARTBEAT_RSP:
      size += m_message.heartbeatRsp.Deserialize (i);
      break;
    case LOOKUP_REQ:
      size += m_message.lookupReq.Deserialize (i);
      break;
    case LOOKUP_RSP:
      size += m_message.lookupRsp.Deserialize (i);
      break;
    case TRACE_RING:
      size += m_message.traceRing.Deserialize (i);
      break;
    default:
      NS_ASSERT (false);
    }
  return size;
}

/* Message Payloads */

/* JOIN_REQ */
uint32_t
ChordMessage::JoinReq::GetSerializedSize (void) const
{
  uint32_t size;
  size = 0;
  return size; 
}

void
ChordMessage::JoinReq::Print (std::ostream &os) const
{
  os << "JoinReq: \nNONE\n";
}

void
ChordMessage::JoinReq::Serialize (Buffer::Iterator &start) const
{
}

uint32_t
ChordMessage::JoinReq::Deserialize (Buffer::Iterator &start)
{
  return GetSerializedSize ();
}

ChordMessage::JoinReq 
ChordMessage::GetJoinReq ()
{
  return m_message.joinReq;
}

void 
ChordMessage::SetJoinReq ()
{
  if (m_messageType == 0)
    {
      m_messageType = JOIN_REQ;
    }
  else
    {
      NS_ASSERT (m_messageType == JOIN_REQ);
    }
}

/* JOIN_RSP */
uint32_t
ChordMessage::JoinRsp::GetSerializedSize (void) const
{
  uint32_t size;
  size = successorNode->GetSerializedSize ();
  return size; 
}

void
ChordMessage::JoinRsp::Print (std::ostream &os) const
{
  os << "JoinRsp: \n";
  os << "Successor Node: " << "\n";
  successorNode->Print (os);
}

void
ChordMessage::JoinRsp::Serialize (Buffer::Iterator &start) const
{
  successorNode->Serialize (start);
}

uint32_t
ChordMessage::JoinRsp::Deserialize (Buffer::Iterator &start)
{
  successorNode = Create<ChordNode> ();
  successorNode->Deserialize (start);
  return GetSerializedSize ();
}


ChordMessage::JoinRsp 
ChordMessage::GetJoinRsp ()
{
  return ChordMessage::m_message.joinRsp;
}

void 
ChordMessage::SetJoinRsp (Ptr<ChordNode> successorNode)
{
  if (m_messageType == 0)
    {
      m_messageType = JOIN_RSP;
    }
  else
    {
      NS_ASSERT (m_messageType == JOIN_RSP);
    }
  m_message.joinRsp.successorNode = successorNode;
}

/* LEAVE_REQ */
uint32_t
ChordMessage::LeaveReq::GetSerializedSize (void) const
{
  uint32_t size;
  size = successorNode->GetSerializedSize () + predecessorNode->GetSerializedSize ();
  return size; 
}

void
ChordMessage::LeaveReq::Print (std::ostream &os) const
{
  os << "LeaveReq: \n";
  os << "Successor Node: " << "\n";
  successorNode->Print (os);
  os << "Predecessor Node: " << "\n";
  predecessorNode->Print (os);
}

void
ChordMessage::LeaveReq::Serialize (Buffer::Iterator &start) const
{
  successorNode->Serialize (start);
  predecessorNode->Serialize (start);
}

uint32_t
ChordMessage::LeaveReq::Deserialize (Buffer::Iterator &start)
{
  successorNode = Create<ChordNode> ();
  successorNode->Deserialize (start);
  predecessorNode = Create<ChordNode> ();
  predecessorNode->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::LeaveReq 
ChordMessage::GetLeaveReq ()
{
  return m_message.leaveReq;
}

void 
ChordMessage::SetLeaveReq (Ptr<ChordNode> successorNode,Ptr<ChordNode> predecessorNode)
{
  m_message.leaveReq.successorNode = successorNode;
  m_message.leaveReq.predecessorNode = predecessorNode;

  if (m_messageType == 0)
    {
      m_messageType = LEAVE_REQ;
    }
  else
    {
      NS_ASSERT (m_messageType == LEAVE_REQ);
    }
}

/* LEAVE_RSP */
uint32_t
ChordMessage::LeaveRsp::GetSerializedSize (void) const
{
  uint32_t size;
  size = successorNode->GetSerializedSize () + predecessorNode->GetSerializedSize ();
  return size; 
}

void
ChordMessage::LeaveRsp::Print (std::ostream &os) const
{
  os << "LeaveRsp: \n";
  os << "Successor Node: " << "\n";
  successorNode->Print (os);
  os << "Predecessor Node: " << "\n";
  predecessorNode->Print (os);
}

void
ChordMessage::LeaveRsp::Serialize (Buffer::Iterator &start) const
{
  successorNode->Serialize (start);
  predecessorNode->Serialize (start);
}

uint32_t
ChordMessage::LeaveRsp::Deserialize (Buffer::Iterator &start)
{
  successorNode = Create<ChordNode> ();
  successorNode->Deserialize (start);
  predecessorNode = Create<ChordNode> ();
  predecessorNode->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::LeaveRsp 
ChordMessage::GetLeaveRsp ()
{
  return m_message.leaveRsp;
}

void 
ChordMessage::SetLeaveRsp (Ptr<ChordNode> successorNode,Ptr<ChordNode> predecessorNode)
{
  if (m_messageType == 0)
    {
      m_messageType = LEAVE_RSP;
    }
  else
    {
      NS_ASSERT (m_messageType == LEAVE_RSP);
    }
  m_message.leaveRsp.successorNode = successorNode;
  m_message.leaveRsp.predecessorNode = predecessorNode;
}

/* STABILIZE_REQ */
uint32_t
ChordMessage::StabilizeReq::GetSerializedSize (void) const
{
  uint32_t size;
  size = successorIdentifier->GetSerializedSize ();
  return size; 
}

void
ChordMessage::StabilizeReq::Print (std::ostream &os) const
{
  os << "StabilizeReq: \n";
  os << "successorIdentifier: " << successorIdentifier << "\n";
}

void
ChordMessage::StabilizeReq::Serialize (Buffer::Iterator &start) const
{
  successorIdentifier->Serialize (start);
}

uint32_t
ChordMessage::StabilizeReq::Deserialize (Buffer::Iterator &start)
{
  successorIdentifier = Create<ChordIdentifier> ();
  successorIdentifier->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::StabilizeReq 
ChordMessage::GetStabilizeReq ()
{
  return m_message.stabilizeReq;
}

void 
ChordMessage::SetStabilizeReq (Ptr<ChordIdentifier> successorIdentifier)
{
  if (m_messageType == 0)
    {
      m_messageType = STABILIZE_REQ;
    }
  else
    {
      NS_ASSERT (m_messageType == STABILIZE_REQ);
    }
  m_message.stabilizeReq.successorIdentifier = successorIdentifier;
}


/* STABILIZE_RSP */
uint32_t
ChordMessage::StabilizeRsp::GetSerializedSize (void) const
{
  uint32_t size;
  size = predecessorNode->GetSerializedSize () + sizeof (uint8_t);
  for (std::vector<Ptr<ChordNode> >::const_iterator nodeIter = successorList.begin (); nodeIter != successorList.end (); nodeIter++)
    {
      Ptr<ChordNode> node = *nodeIter;
      size = size + node->GetSerializedSize ();
    }
  return size; 
}

void
ChordMessage::StabilizeRsp::Print (std::ostream &os) const
{
  os << "StabilizeRsp: \n";
  os << "Predecessor Node: " << "\n";
  predecessorNode->Print (os);
  os << "successorListSize: " << successorListSize << "\n";
  for (std::vector<Ptr<ChordNode> >::const_iterator nodeIter = successorList.begin (); nodeIter != successorList.end (); nodeIter++)
    {
      Ptr<ChordNode> node = *nodeIter;
      os << "***\n";
      os << "Successor Node: " << "\n";
      node->Print (os);
    }
}

void
ChordMessage::StabilizeRsp::Serialize (Buffer::Iterator &start) const
{
  predecessorNode->Serialize (start);
  // Write successor list size
  start.WriteU8 (successorListSize);
  // Write entire list
  for (std::vector<Ptr<ChordNode> >::const_iterator nodeIter = successorList.begin (); nodeIter != successorList.end (); nodeIter++)
    {
      Ptr<ChordNode> node = *nodeIter;
      node->Serialize (start);
    }
}

uint32_t
ChordMessage::StabilizeRsp::Deserialize (Buffer::Iterator &start)
{
  predecessorNode = Create<ChordNode> ();
  predecessorNode->Deserialize (start);
  // Deserialize successor list
  successorListSize = start.ReadU8 ();
  for (int i = 0; i < successorListSize; i++)
    {
      // Store in list
      Ptr<ChordNode> chordNode = Create<ChordNode> ();
      chordNode->Deserialize (start);
      successorList.push_back (chordNode);
    }
  return GetSerializedSize ();
}

ChordMessage::StabilizeRsp 
ChordMessage::GetStabilizeRsp ()
{
  return m_message.stabilizeRsp;
}

void 
ChordMessage::SetStabilizeRsp (Ptr<ChordNode> predecessorNode,uint8_t successorListSize,Ptr<ChordNode> node)
{
  if (m_messageType == 0)
    {
      m_messageType = STABILIZE_RSP;
    }
  else
    {
      NS_ASSERT (m_messageType == STABILIZE_RSP);
    }
  m_message.stabilizeRsp.predecessorNode = predecessorNode;
  m_message.stabilizeRsp.successorListSize = successorListSize;
  m_message.stabilizeRsp.successorList.push_back (node);
}


/* FINGER_REQ */
uint32_t
ChordMessage::FingerReq::GetSerializedSize (void) const
{
  uint32_t size;
  size = requestedIdentifier->GetSerializedSize ();
  return size; 
}

void
ChordMessage::FingerReq::Print (std::ostream &os) const
{
  os << "FingerReq: \n";
  os << "requestedIdentifier: " << requestedIdentifier << "\n";
}

void
ChordMessage::FingerReq::Serialize (Buffer::Iterator &start) const
{
  requestedIdentifier->Serialize (start);
}

uint32_t
ChordMessage::FingerReq::Deserialize (Buffer::Iterator &start)
{
  requestedIdentifier = Create<ChordIdentifier> ();
  requestedIdentifier->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::FingerReq 
ChordMessage::GetFingerReq ()
{
  return m_message.fingerReq;
}

void 
ChordMessage::SetFingerReq (Ptr<ChordIdentifier> requestedIdentifier)
{
  if (m_messageType == 0)
    {
      m_messageType = FINGER_REQ;
    }
  else
    {
      NS_ASSERT (m_messageType == FINGER_REQ);
    }
  m_message.fingerReq.requestedIdentifier = requestedIdentifier;
}

/* FINGER_RSP */
uint32_t
ChordMessage::FingerRsp::GetSerializedSize (void) const
{
  uint32_t size;
  size = requestedIdentifier->GetSerializedSize () + fingerNode->GetSerializedSize ();
  return size; 
}

void
ChordMessage::FingerRsp::Print (std::ostream &os) const
{
  os << "FingerRsp: \n";
  os << "requestedIdentifier: " << requestedIdentifier << "\n";
  os << "Finger Node: " << "\n";
  fingerNode->Print (os);
}

void
ChordMessage::FingerRsp::Serialize (Buffer::Iterator &start) const
{
  requestedIdentifier->Serialize (start);
  fingerNode->Serialize (start);
}

uint32_t
ChordMessage::FingerRsp::Deserialize (Buffer::Iterator &start)
{
  requestedIdentifier = Create<ChordIdentifier> ();
  requestedIdentifier->Deserialize (start);
  fingerNode = Create<ChordNode> ();
  fingerNode->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::FingerRsp 
ChordMessage::GetFingerRsp ()
{
  return m_message.fingerRsp;
}

void 
ChordMessage::SetFingerRsp (Ptr<ChordIdentifier> requestedIdentifier,Ptr<ChordNode> fingerNode)
{
  if (m_messageType == 0)
    {
      m_messageType = FINGER_RSP;
    }
  else
    {
      NS_ASSERT (m_messageType == FINGER_RSP);
    }
  m_message.fingerRsp.requestedIdentifier = requestedIdentifier;
  m_message.fingerRsp.fingerNode = fingerNode;
}

/* HEARTBEAT_REQ */
uint32_t
ChordMessage::HeartbeatReq::GetSerializedSize (void) const
{
  uint32_t size;
  size = predecessorIdentifier->GetSerializedSize ();
  return size; 
}

void
ChordMessage::HeartbeatReq::Print (std::ostream &os) const
{
  os << "HeartbeatReq: \n";
  os << "predecessorIdentifier: " << predecessorIdentifier << "\n";
}

void
ChordMessage::HeartbeatReq::Serialize (Buffer::Iterator &start) const
{
  predecessorIdentifier->Serialize (start);
}

uint32_t
ChordMessage::HeartbeatReq::Deserialize (Buffer::Iterator &start)
{
  predecessorIdentifier = Create<ChordIdentifier> ();
  predecessorIdentifier->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::HeartbeatReq 
ChordMessage::GetHeartbeatReq ()
{
  return m_message.heartbeatReq;
}

void 
ChordMessage::SetHeartbeatReq (Ptr<ChordIdentifier> predecessorIdentifier)
{
  if (m_messageType == 0)
    {
      m_messageType = HEARTBEAT_REQ;
    }
  else
    {
      NS_ASSERT (m_messageType == HEARTBEAT_REQ);
    }
  m_message.heartbeatReq.predecessorIdentifier = predecessorIdentifier;
}

/* HEARTBEAT_RSP */
uint32_t
ChordMessage::HeartbeatRsp::GetSerializedSize (void) const
{
  uint32_t size;
  size = successorNode->GetSerializedSize () + sizeof(uint8_t);
  for (std::vector<Ptr<ChordNode> >::const_iterator nodeIter = predecessorList.begin (); nodeIter != predecessorList.end (); nodeIter++)
    {
      Ptr<ChordNode> node = *nodeIter;
      size = size + node->GetSerializedSize ();
    }
  return size; 
}

void
ChordMessage::HeartbeatRsp::Print (std::ostream &os) const
{
  os << "HeartbeatRsp: \n";
  os << "Successor Node: " << "\n";
  successorNode->Print (os);
  for (std::vector<Ptr<ChordNode> >::const_iterator nodeIter = predecessorList.begin (); nodeIter != predecessorList.end (); nodeIter++)
    {
      Ptr<ChordNode> node = *nodeIter;
      os << "***\n";
      os << "Predecessor Node: " << "\n";
      node->Print (os);
    }
}

void
ChordMessage::HeartbeatRsp::Serialize (Buffer::Iterator &start) const
{
  successorNode->Serialize (start);
  // Write successor list size
  start.WriteU8 (predecessorListSize);
  // Write entire list
  for (std::vector<Ptr<ChordNode> >::const_iterator nodeIter = predecessorList.begin (); nodeIter != predecessorList.end (); nodeIter++)
    {
      Ptr<ChordNode> node = *nodeIter;
      node->Serialize (start);
    }
}

uint32_t
ChordMessage::HeartbeatRsp::Deserialize (Buffer::Iterator &start)
{
  successorNode = Create<ChordNode> ();
  successorNode->Deserialize (start);
  // Deserialize successor list
  predecessorListSize = start.ReadU8 ();
  for (int i = 0; i < predecessorListSize; i++)
    {
      // Store in list
      Ptr<ChordNode> chordNode = Create<ChordNode> ();
      chordNode->Deserialize (start);
      predecessorList.push_back (chordNode);
    }
  return GetSerializedSize ();
}

ChordMessage::HeartbeatRsp 
ChordMessage::GetHeartbeatRsp ()
{
  return m_message.heartbeatRsp;
}

void 
ChordMessage::SetHeartbeatRsp (Ptr<ChordNode> successorNode,uint8_t predecessorListSize,Ptr<ChordNode> node)
{
  if (m_messageType == 0)
    {
      m_messageType = HEARTBEAT_RSP;
    }
  else
    {
      NS_ASSERT (m_messageType == HEARTBEAT_RSP);
    }
  m_message.heartbeatRsp.successorNode = successorNode;
  m_message.heartbeatRsp.predecessorListSize = predecessorListSize;
  m_message.heartbeatRsp.predecessorList.push_back (node);
}

/* LOOKUP_REQ */
uint32_t
ChordMessage::LookupReq::GetSerializedSize (void) const
{
  uint32_t size;
  size = requestedIdentifier->GetSerializedSize ();
  return size; 
}

void
ChordMessage::LookupReq::Print (std::ostream &os) const
{
  os << "LookupReq: \n";
  os << "requestedIdentifier: " << requestedIdentifier << "\n";
}

void
ChordMessage::LookupReq::Serialize (Buffer::Iterator &start) const
{
  requestedIdentifier->Serialize (start);
}

uint32_t
ChordMessage::LookupReq::Deserialize (Buffer::Iterator &start)
{
  requestedIdentifier = Create<ChordIdentifier> ();
  requestedIdentifier->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::LookupReq 
ChordMessage::GetLookupReq ()
{
  return m_message.lookupReq;
}

void 
ChordMessage::SetLookupReq (Ptr<ChordIdentifier> requestedIdentifier)
{
  if (m_messageType == 0)
    {
      m_messageType = LOOKUP_REQ;
    }
  else
    {
      NS_ASSERT (m_messageType == LOOKUP_REQ);
    }
  m_message.lookupReq.requestedIdentifier = requestedIdentifier;
}

/* LOOKUP_RSP */
uint32_t
ChordMessage::LookupRsp::GetSerializedSize (void) const
{
  uint32_t size;
  size = resolvedNode->GetSerializedSize ();
  return size; 
}

void
ChordMessage::LookupRsp::Print (std::ostream &os) const
{
  os << "LookupRsp: \n";
  os << "Resolved Node: " << "\n";
  resolvedNode->Print (os);
}

void
ChordMessage::LookupRsp::Serialize (Buffer::Iterator &start) const
{
  resolvedNode->Serialize (start);
}

uint32_t
ChordMessage::LookupRsp::Deserialize (Buffer::Iterator &start)
{
  resolvedNode = Create<ChordNode> ();
  resolvedNode->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::LookupRsp 
ChordMessage::GetLookupRsp ()
{
  return m_message.lookupRsp;
} 

void 
ChordMessage::SetLookupRsp (Ptr<ChordNode> resolvedNode)
{
  if (m_messageType == 0)
    {
      m_messageType = LOOKUP_RSP;
    }
  else
    {
      NS_ASSERT (m_messageType == LOOKUP_RSP);
    }
  m_message.lookupRsp.resolvedNode = resolvedNode;
}


/* TRACE_RING */
uint32_t
ChordMessage::TraceRing::GetSerializedSize (void) const
{
  uint32_t size;
  size = successorIdentifier->GetSerializedSize ();
  return size; 
}

void
ChordMessage::TraceRing::Print (std::ostream &os) const
{
  os << "TraceRing: \n";
  os << "successorIdentifier: " << successorIdentifier << "\n";
}

void
ChordMessage::TraceRing::Serialize (Buffer::Iterator &start) const
{
  successorIdentifier->Serialize (start);
}

uint32_t
ChordMessage::TraceRing::Deserialize (Buffer::Iterator &start)
{
  successorIdentifier = Create<ChordIdentifier> ();
  successorIdentifier->Deserialize (start);
  return GetSerializedSize ();
}

ChordMessage::TraceRing 
ChordMessage::GetTraceRing ()
{
  return m_message.traceRing;
}

void 
ChordMessage::SetLookupRsp (Ptr<ChordIdentifier> successorIdentifier)
{
  if (m_messageType == 0)
    {
      m_messageType = TRACE_RING;
    }
  else
    {
      NS_ASSERT (m_messageType == TRACE_RING);
    }

  m_message.traceRing.successorIdentifier = successorIdentifier;
}

} // namespace ns3
