# High Level Design (HLD) vs Low Level Design (LLD)

The foundation of any successful software system starts with a clear
design. In software engineering, the design phase is mainly divided into
High-Level Design (HLD) and Low-Level Design (LLD). Both help developers
build scalable, maintainable, and efficient systems.

------------------------------------------------------------------------

# 1. High Level Design (HLD)

## Definition

High Level Design describes the overall architecture of the system. It
explains what components exist in the system and how they interact with
each other, without focusing on implementation details.

## In Simple Words

HLD shows the big picture of the system.

## Key Focus Areas

-   System architecture
-   Major modules/services
-   Communication between services
-   Databases used
-   External integrations

## Things Included in HLD

-   System architecture (Monolith / Microservices)
-   Major services or modules
-   API communication
-   Load balancers
-   Databases
-   Message queues
-   Caching systems
-   CDN usage

------------------------------------------------------------------------

# Example: Instagram (HLD)

Major components might include:

-   User Service → manages user accounts
-   Post Service → manages posts and images
-   Feed Service → generates user feeds
-   Notification Service → sends notifications
-   Database → stores users, posts, comments
-   CDN → delivers images quickly

Goal of HLD: What components exist and how do they communicate?

------------------------------------------------------------------------

# 2. Low Level Design (LLD)

## Definition

Low Level Design describes the detailed implementation of each component
defined in HLD.

It focuses on how the system will actually be built in code.

## In Simple Words

LLD explains how each module works internally.

## Key Focus Areas

-   Classes and objects
-   Functions and methods
-   Data structures
-   Algorithms
-   Database schemas
-   Design patterns

## Things Included in LLD

-   Class diagrams
-   Method definitions
-   Object relationships
-   Database tables
-   Data structures used
-   Detailed logic

------------------------------------------------------------------------

# Example: Instagram Post Service (LLD)

Classes: - User - Post - Comment - Like

Methods: - createPost() - deletePost() - likePost() - addComment() -
getPostById()

Database Schema Example:

Post - post_id - user_id - caption - image_url - created_at

Goal of LLD: How will each component actually be implemented?

------------------------------------------------------------------------

# Difference Between HLD and LLD

  Feature   HLD                           LLD
  --------- ----------------------------- ---------------------------------
  Meaning   Overall system architecture   Detailed implementation
  Focus     System components             Internal module logic
  Level     Abstract                      Detailed
  Used By   System architects             Developers
  Output    Architecture diagrams         Class diagrams / code structure

------------------------------------------------------------------------

# Real World Example: Building a House

## High Level Design

-   Number of floors
-   Layout of rooms
-   Kitchen location
-   Parking area
-   Garden space

This is like the architect's blueprint.

## Low Level Design

-   Wall thickness
-   Electrical wiring plan
-   Plumbing system
-   Door and window measurements
-   Materials used

This is like the construction details used by engineers.

------------------------------------------------------------------------

# Conclusion

Both HLD and LLD are essential parts of software design.

-   HLD defines the overall structure of the system
-   LLD defines the detailed implementation of each component

Together they ensure the system is scalable, maintainable, and
efficient.
