---
layout: default
title: Architecture
nav_order: 3
has_children: true
---

# Architecture

## Introduction

The KISS framework follows the *layered* architecture pattern. Each layer may contain multiple components. KISS consists of the following layers:

| Layer | Responsibilities |
|-------|------------------|
| Application | Offers a programming interface to applications built on top of the framework |
| Discretization | Manages space and time discretizations of objects in the Mathematics and Domain layers |
| Mathematics | Contains abstractions that represent the governing equations of the mathematical model |
| Domain | Models the relevant objects, concepts and properties of the physical world in a single representation, independent of file formats and discretization types |
| Data | Performs file I/O, provides abstraction from file formats |

Higher-level layers are allowed to depend on lower layers, upward dependencies are not allowed (dependency inversion techniques can be used if necessary). Components should preferably only depend on components in neighbouring layers, however 'skipping' layers is allowed. Intra-layer dependecies should be limited.

In addition, there is an infrastructure 'layer' that offers services and utilities that can be used in all other layers.

| Layer | Responsibilities |
|-------|------------------|
| Infrastructure | Offers layer-independent services (logging, common data types, etc.) |

*Figure 1* shows the architecture layers:

<figure>
  <img src="images/architecture_layers.png" alt="Component View">
  <figcaption>Figure 1 - Architecture Layers</figcaption>
</figure>

*Figure 2* shows the components that form the framework:

<figure>
  <img src="images/framework_components.png" alt="Component View">
  <figcaption>Figure 2 - Framework Components</figcaption>
</figure>

The KISS framework depends on several third-party components, which are shown in grey in *Figure 2*.

*Figure 3* shows the KISS framework components in their architectural layers:

<figure>
  <img src="images/layers_with_components.png" alt="Component View">
  <figcaption>Figure 3 - Layers and Components</figcaption>
</figure>


## Design decisions

An overview of the design decisions for the current prototype and possible extensions can be found [here](design_decisions.md).

## Architecture layers

The different layers of KISS are described in the sections below.

- [The Infrastructure layer](../Framework/Infrastructure/readme.md)

- [The Data layer](../Framework/Data/readme.md)

- [The Domain layer](../Framework/Domain/readme.md)

- [The Mathematics layer](../Framework/Math/readme.md)

- [The Discretization layer](../Framework/Discretization/readme.md)

- [The Applications layer](../Applications/readme.md)
